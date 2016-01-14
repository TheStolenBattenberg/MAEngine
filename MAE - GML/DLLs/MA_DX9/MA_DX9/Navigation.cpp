#include "Navigation.h"
#include "Utils.h"

MANavigation* manav = nullptr;

MANavMesh::MANavMesh()
{
	m_ctx = new rcContext();
	m_navQuery = dtAllocNavMeshQuery();
	m_cellSize = 0.2f;
	m_cellHeight = 0.4f;
	m_agentHeight = 3.f;
	m_agentRadius = 1.f;
	m_agentMaxClimb = 1.f;
	m_agentMaxSlope = 45.f;
	m_regionMinSize = 16;
	m_regionMergeSize = 20;
	m_edgeMaxLen = 12.f;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6.f;
	m_detailSampleDist = 6.f;
	m_detailSampleMaxError = 1.f;
}

MANavMesh::~MANavMesh()
{
	delete m_ctx;
	dtFreeNavMeshQuery(m_navQuery);
	cleanup();
}

void MANavMesh::cleanup()
{
	if (m_triareas) delete[] m_triareas;
	dtFreeNavMesh(m_navMesh);
	rcFreeHeightField(m_solid);
	rcFreeCompactHeightfield(m_chf);
	rcFreeContourSet(m_cset);
	rcFreePolyMesh(m_pmesh);
	rcFreePolyMeshDetail(m_dmesh);
	m_navMesh = nullptr;
	m_triareas = nullptr;
	m_solid = nullptr;
	m_chf = nullptr;
	m_cset = nullptr;
	m_pmesh = nullptr;
	m_dmesh = nullptr;
	m_connection_verts.clear();
	m_connection_rad.clear();
	m_connection_areas.clear();
	m_connection_flags.clear();
	m_connection_userIDs.clear();
	m_connection_dir.clear();
	m_meshes.clear();
}

int MANavMesh::beginBuild(float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
	cleanup();

	float bmin[3] = { minx, minz, miny };
	float bmax[3] = { maxx, maxz, maxy };

	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = m_cellSize;
	m_cfg.ch = m_cellHeight;
	m_cfg.walkableSlopeAngle = m_agentMaxSlope;
	m_cfg.walkableHeight = (int)ceilf(m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int)floorf(m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int)ceilf(m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int)(m_edgeMaxLen / m_cellSize);
	m_cfg.maxSimplificationError = m_edgeMaxError;
	m_cfg.minRegionArea = (int)rcSqr(m_regionMinSize);
	m_cfg.mergeRegionArea = (int)rcSqr(m_regionMergeSize);
	m_cfg.maxVertsPerPoly = (int)m_vertsPerPoly;
	m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
	m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;
	rcVcopy(m_cfg.bmin, bmin);
	rcVcopy(m_cfg.bmax, bmax);

	return 1;
}

int MANavMesh::addMesh(float* verts, int nverts, int* tris, int ntris, float* matrix)
{
	m_meshes.push_back({verts, nverts, tris, ntris, D3DXMATRIX(matrix) });
	return 1;
}

int MANavMesh::endBuild(bool async)
{
	if (async) {
		buildStatus = 0;
		m_build_thread = std::thread(&MANavMesh::build, this);
		return 1;
	}
	build();
	return buildStatus;
}

void MANavMesh::build()
{
	rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

	m_solid = rcAllocHeightfield();
	rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch);

	for (auto i : m_meshes) {
		int* tris = i.tris;
		int ntris = i.ntris;
		float* verts = i.verts;
		int nverts = i.nverts;
		D3DXMATRIX d3dmatrix = i.matrix;

		int* tbuffer = nullptr;
		if (!tris) {
			tris = new int[nverts / 3];
			for (int i = 0; i < nverts / 3; ++i) {
				tris[i] = i;
			}
			ntris = nverts / 9;
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

		m_triareas = new uint8_t[ntris];
		memset(m_triareas, 0, ntris*sizeof(uint8_t));

		rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, vbuffer, nverts, tris, ntris, m_triareas);
		rcRasterizeTriangles(m_ctx, vbuffer, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb);

		delete[] m_triareas;
		m_triareas = nullptr;
		delete[] vbuffer;
		if (tbuffer) delete[] tbuffer;
	}
	m_meshes.clear();

	rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);

	m_chf = rcAllocCompactHeightfield();
	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf)) {
		buildStatus = -1;
		return;
	}

	rcFreeHeightField(m_solid);
	m_solid = nullptr;

	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf)) {
		buildStatus = -2;
		return;
	}

	if (!rcBuildDistanceField(m_ctx, *m_chf)) {
		buildStatus = -3;
		return;
	}
	if (!rcBuildRegions(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea)) {
		buildStatus = -4;
		return;
	}

	m_cset = rcAllocContourSet();
	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset)) {
		buildStatus = -5;
		return;
	}

	m_pmesh = rcAllocPolyMesh();
	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh)) {
		buildStatus = -6;
		return;
	}

	m_dmesh = rcAllocPolyMeshDetail();
	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh)) {
		buildStatus = -7;
		return;
	}

	rcFreeCompactHeightfield(m_chf);
	m_chf = nullptr;
	rcFreeContourSet(m_cset);
	m_cset = nullptr;

	if (m_cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON) {
		buildStatus = -8;
		return;
	}

	for (int i = 0; i < m_pmesh->npolys; ++i) {
		m_pmesh->flags[i] = 1;
	}

	dtNavMeshCreateParams params;
	memset(&params, 0, sizeof(params));
	params.verts = m_pmesh->verts;
	params.vertCount = m_pmesh->nverts;
	params.polys = m_pmesh->polys;
	params.polyAreas = m_pmesh->areas;
	params.polyFlags = m_pmesh->flags;
	params.polyCount = m_pmesh->npolys;
	params.nvp = m_pmesh->nvp;
	params.detailMeshes = m_dmesh->meshes;
	params.detailVerts = m_dmesh->verts;
	params.detailVertsCount = m_dmesh->nverts;
	params.detailTris = m_dmesh->tris;
	params.detailTriCount = m_dmesh->ntris;	
	params.offMeshConVerts = m_connection_verts.data();
	params.offMeshConRad = m_connection_rad.data();
	params.offMeshConDir = m_connection_dir.data();
	params.offMeshConAreas = m_connection_areas.data();
	params.offMeshConFlags = m_connection_flags.data();
	params.offMeshConUserID = m_connection_userIDs.data();
	params.offMeshConCount = m_connection_flags.size();
	params.walkableHeight = m_agentHeight;
	params.walkableRadius = m_agentRadius;
	params.walkableClimb = m_agentMaxClimb;
	rcVcopy(params.bmin, m_pmesh->bmin);
	rcVcopy(params.bmax, m_pmesh->bmax);
	params.cs = m_cfg.cs;
	params.ch = m_cfg.ch;
	params.buildBvTree = true;

	uint8_t* navData = nullptr;
	int navDataSize = 0;
	if (!dtCreateNavMeshData(&params, &navData, &navDataSize)) {
		buildStatus = -9;
		return;
	}

	m_navMesh = dtAllocNavMesh();
	if (!m_navMesh) {
		dtFree(navData);
		buildStatus = -10;
		return;
	}

	dtStatus status;
	status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
	if (dtStatusFailed(status)) {
		dtFree(navData);
		buildStatus = -11;
		return;
	}

	status = m_navQuery->init(m_navMesh, 2048);
	
	if (dtStatusFailed(status)) {
		buildStatus = -12;
		return;
	}

	buildStatus = 1;
}

bool MANavMesh::addLink(float* v1, float* v2, int dir, float radius)
{
	m_connection_verts.push_back(-v1[0]);
	m_connection_verts.push_back(v1[2]);
	m_connection_verts.push_back(v1[1]);
	m_connection_verts.push_back(-v2[0]);
	m_connection_verts.push_back(v2[2]);
	m_connection_verts.push_back(v2[1]);
	m_connection_rad.push_back(radius);
	m_connection_dir.push_back(dir);
	m_connection_areas.push_back(1);
	m_connection_flags.push_back(1);
	m_connection_userIDs.push_back(1);
	return 1;
}

MANavigation::~MANavigation()
{
	ClearVector(NavMeshes);
}
