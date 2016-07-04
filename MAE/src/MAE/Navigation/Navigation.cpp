#include <MAE/Navigation/Navigation.h>
#include <MAE/Core/Utils.h>

MANavigation manav;

NavMesh::NavMesh()
{
	context = new rcContext();
	navQuery = dtAllocNavMeshQuery();
	cellSize = 0.2f;
	cellHeight = 0.4f;
	agentHeight = 3.f;
	agentRadius = 1.f;
	agentMaxClimb = 1.f;
	agentMaxSlope = 45.f;
	regionMinSize = 16;
	regionMergeSize = 20;
	edgeMaxLen = 12.f;
	edgeMaxError = 1.3f;
	vertsPerPoly = 6.f;
	detailSampleDist = 6.f;
	detailSampleMaxError = 1.f;
}

NavMesh::~NavMesh()
{
	delete context;
	dtFreeNavMeshQuery(navQuery);
	cleanup();
}

void NavMesh::cleanup()
{
	if (triAreas) delete[] triAreas;
	dtFreeNavMesh(navMesh);
	rcFreeHeightField(heightfield);
	rcFreeCompactHeightfield(compactHeightfield);
	rcFreeContourSet(contourSet);
	rcFreePolyMesh(polyMesh);
	rcFreePolyMeshDetail(detailMesh);
	navMesh = nullptr;
	triAreas = nullptr;
	heightfield = nullptr;
	compactHeightfield = nullptr;
	contourSet = nullptr;
	polyMesh = nullptr;
	detailMesh = nullptr;
	connections.clear();
	meshes.clear();
}

int NavMesh::beginBuild(float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
	cleanup();

	float bmin[3] = { minx, minz, miny };
	float bmax[3] = { maxx, maxz, maxy };

	memset(&config, 0, sizeof(config));
	config.cs = cellSize;
	config.ch = cellHeight;
	config.walkableSlopeAngle = agentMaxSlope;
	config.walkableHeight = (int)ceilf(agentHeight / config.ch);
	config.walkableClimb = (int)floorf(agentMaxClimb / config.ch);
	config.walkableRadius = (int)ceilf(agentRadius / config.cs);
	config.maxEdgeLen = (int)(edgeMaxLen / cellSize);
	config.maxSimplificationError = edgeMaxError;
	config.minRegionArea = (int)rcSqr(regionMinSize);
	config.mergeRegionArea = (int)rcSqr(regionMergeSize);
	config.maxVertsPerPoly = (int)vertsPerPoly;
	config.detailSampleDist = detailSampleDist < 0.9f ? 0 : cellSize * detailSampleDist;
	config.detailSampleMaxError = cellHeight * detailSampleMaxError;
	rcVcopy(config.bmin, bmin);
	rcVcopy(config.bmax, bmax);

	return 1;
}

int NavMesh::addMesh(float* verts, int nverts, int* tris, int ntris, float* matrix)
{
	meshes.push_back({verts, nverts, tris, ntris, D3DXMATRIX(matrix) });
	return 1;
}

int NavMesh::endBuild(bool async)
{
	if (async) {
		buildStatus = 0;
		buildThread = std::thread(&NavMesh::build, this);
		return 1;
	}
	build();
	return buildStatus;
}

void NavMesh::build()
{
	rcCalcGridSize(config.bmin, config.bmax, config.cs, &config.width, &config.height);

	heightfield = rcAllocHeightfield();
	rcCreateHeightfield(context, *heightfield, config.width, config.height, config.bmin, config.bmax, config.cs, config.ch);

	for (auto i : meshes) {
		int* tris = i.tris;
		int ntris = i.ntris;
		float* verts = i.verts;
		int nverts = i.nverts;
		D3DXMATRIX d3dmatrix = i.matrix;

		int* tbuffer = nullptr;
		if (!tris) {
			tris = new int[nverts];
			for (int i = 0; i < nverts; ++i) {
				tris[i] = i;
			}
			ntris = nverts / 3;
			tbuffer = tris;
		}
		float* vbuffer = new float[nverts * 3];		
		for (int i = 0; i < nverts; ++i) {
			float x = verts[i * 3];
			float y = verts[i * 3 + 1];
			float z = verts[i * 3 + 2];
			D3DXVECTOR3 v(x, y, z);
			D3DXVECTOR3 vOut;
			D3DXVec3TransformCoord(&vOut, &v, &d3dmatrix);
			vbuffer[i * 3] = -vOut.x;
			vbuffer[i * 3 + 1] = vOut.z;
			vbuffer[i * 3 + 2] = vOut.y;
		}

		triAreas = new uint8_t[ntris];
		memset(triAreas, 0, ntris*sizeof(uint8_t));

		rcMarkWalkableTriangles(context, config.walkableSlopeAngle, vbuffer, nverts, tris, ntris, triAreas);
		rcRasterizeTriangles(context, vbuffer, nverts, tris, triAreas, ntris, *heightfield, config.walkableClimb);

		delete[] triAreas;
		triAreas = nullptr;
		delete[] vbuffer;
		if (tbuffer) delete[] tbuffer;
	}
	meshes.clear();

	rcFilterLowHangingWalkableObstacles(context, config.walkableClimb, *heightfield);
	rcFilterLedgeSpans(context, config.walkableHeight, config.walkableClimb, *heightfield);
	rcFilterWalkableLowHeightSpans(context, config.walkableHeight, *heightfield);

	compactHeightfield = rcAllocCompactHeightfield();
	if (!rcBuildCompactHeightfield(context, config.walkableHeight, config.walkableClimb, *heightfield, *compactHeightfield)) {
		buildStatus = -1;
		return;
	}

	rcFreeHeightField(heightfield);
	heightfield = nullptr;

	if (!rcErodeWalkableArea(context, config.walkableRadius, *compactHeightfield)) {
		buildStatus = -2;
		return;
	}

	if (!rcBuildDistanceField(context, *compactHeightfield)) {
		buildStatus = -3;
		return;
	}
	if (!rcBuildRegions(context, *compactHeightfield, 0, config.minRegionArea, config.mergeRegionArea)) {
		buildStatus = -4;
		return;
	}

	contourSet = rcAllocContourSet();
	if (!rcBuildContours(context, *compactHeightfield, config.maxSimplificationError, config.maxEdgeLen, *contourSet)) {
		buildStatus = -5;
		return;
	}

	polyMesh = rcAllocPolyMesh();
	if (!rcBuildPolyMesh(context, *contourSet, config.maxVertsPerPoly, *polyMesh)) {
		buildStatus = -6;
		return;
	}

	detailMesh = rcAllocPolyMeshDetail();
	if (!rcBuildPolyMeshDetail(context, *polyMesh, *compactHeightfield, config.detailSampleDist, config.detailSampleMaxError, *detailMesh)) {
		buildStatus = -7;
		return;
	}

	rcFreeCompactHeightfield(compactHeightfield);
	compactHeightfield = nullptr;
	rcFreeContourSet(contourSet);
	contourSet = nullptr;

	if (config.maxVertsPerPoly > DT_VERTS_PER_POLYGON) {
		buildStatus = -8;
		return;
	}

	for (int i = 0; i < polyMesh->npolys; ++i) {
		polyMesh->flags[i] = 1;
	}

	dtNavMeshCreateParams params;
	memset(&params, 0, sizeof(params));
	params.verts = polyMesh->verts;
	params.vertCount = polyMesh->nverts;
	params.polys = polyMesh->polys;
	params.polyAreas = polyMesh->areas;
	params.polyFlags = polyMesh->flags;
	params.polyCount = polyMesh->npolys;
	params.nvp = polyMesh->nvp;
	params.detailMeshes = detailMesh->meshes;
	params.detailVerts = detailMesh->verts;
	params.detailVertsCount = detailMesh->nverts;
	params.detailTris = detailMesh->tris;
	params.detailTriCount = detailMesh->ntris;

	std::vector<float> verts;
	std::vector<float> rad;
	std::vector<uint8_t> dir;
	std::vector<uint8_t> areas;
	std::vector<uint16_t> flags;
	std::vector<uint32_t> userIDs;
	for (auto i : connections) {
		verts.push_back(i.v1[0]);
		verts.push_back(i.v1[1]);
		verts.push_back(i.v1[2]);
		verts.push_back(i.v2[0]);
		verts.push_back(i.v2[1]);
		verts.push_back(i.v2[2]);
		rad.push_back(i.rad);
		dir.push_back(i.dir);
		areas.push_back(i.area);
		flags.push_back(i.flag);
		userIDs.push_back(i.userID);
	}
	params.offMeshConVerts = verts.data();
	params.offMeshConRad = rad.data();
	params.offMeshConDir = dir.data();
	params.offMeshConAreas = areas.data();
	params.offMeshConFlags = flags.data();
	params.offMeshConUserID = userIDs.data();

	params.offMeshConCount = flags.size();
	params.walkableHeight = agentHeight;
	params.walkableRadius = agentRadius;
	params.walkableClimb = agentMaxClimb;
	rcVcopy(params.bmin, polyMesh->bmin);
	rcVcopy(params.bmax, polyMesh->bmax);
	params.cs = config.cs;
	params.ch = config.ch;
	params.buildBvTree = true;

	uint8_t* navData = nullptr;
	int navDataSize = 0;
	if (!dtCreateNavMeshData(&params, &navData, &navDataSize)) {
		buildStatus = -9;
		return;
	}

	navMesh = dtAllocNavMesh();
	if (!navMesh) {
		dtFree(navData);
		buildStatus = -10;
		return;
	}

	dtStatus status;
	status = navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
	if (dtStatusFailed(status)) {
		dtFree(navData);
		buildStatus = -11;
		return;
	}

	status = navQuery->init(navMesh, 2048);
	
	if (dtStatusFailed(status)) {
		buildStatus = -12;
		return;
	}

	buildStatus = 1;
}

bool NavMesh::addLink(float* v1, float* v2, int dir, float radius)
{
	connections.push_back({ -v1[0], v1[2], v1[1], -v2[0], v2[2], v2[1], radius, (uint8_t)dir, 1, 1, 1 });
	return 1;
}

MANavigation::~MANavigation()
{
	freeContainer(navMeshes);
}
