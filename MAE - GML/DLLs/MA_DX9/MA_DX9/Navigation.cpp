#include "Navigation.h"
#include "Main.h"
#include "NavMeshDebugDraw.h"
#include "DetourDebugDraw.h"
#include <iostream>

MANavigation* manav = nullptr;

MANavigation::MANavigation()
{
	m_ctx = new rcContext();
	m_navQuery = dtAllocNavMeshQuery();
}

MANavigation::~MANavigation()
{
	delete m_ctx;
	dtFreeNavMeshQuery(m_navQuery);
	cleanup();
}

void MANavigation::cleanup()
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
}

int MANavigation::createNavMesh(char* filename)
{
	//free previous navmesh
	cleanup();

	int ntris = 0;
	int nverts = 0;
	float* verts = nullptr;
	int* tris = nullptr;
	float bmin[3] = { -50, -50, -50 };
	float bmax[3] = { 50, 50, 50 };

	/*
		Load test mesh from GM model file.
		This function should take in a vertex buffer instead.
	*/
	std::string line;
	std::ifstream file(filename);
	std::vector<float> vertices;
	std::vector<int> triangles;
	if (file){
		int version, lines;
		file >> version >> lines;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		int vertex_count = 0;
		for (int i = 0; i < lines; i++){
			int n;
			file >> n;
			if (n > 1 && n < 10){
				float x, y, z;
				file >> x >> y >> z;

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				vertex_count++;
				if (vertex_count == 3){
					triangles.push_back(vertices.size()-2);
					triangles.push_back(vertices.size()-1);
					triangles.push_back(vertices.size());
					vertex_count = 0;
				}
			}
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		file.close();
	}
	else return 0;

	verts = &vertices[0];
	nverts = vertices.size()/3;
	tris = &triangles[0];
	ntris = triangles.size()/3;

	std::cout << "ntris: " << ntris << std::endl;
	std::cout << "nverts: " << nverts << std::endl;

	//TODO: make functions to set these
	m_cellSize = 0.3f;
	m_cellHeight = 0.2f;
	m_agentHeight = 2.f;
	m_agentRadius = 0.6f;
	m_agentMaxClimb = 0.9f;
	m_agentMaxSlope = 45.f;
	m_regionMinSize = 8;
	m_regionMergeSize = 20;
	m_edgeMaxLen = 12.f;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6.f;
	m_detailSampleDist = 6.f;
	m_detailSampleMaxError = 1.f;

	//set config
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

	rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

	m_solid = rcAllocHeightfield();
	if (!m_solid) return -1;
	if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch)) return -2;

	//TODO: Allocate this on the stack instead?
	m_triareas = new unsigned char[ntris];
	memset(m_triareas, 0, ntris*sizeof(unsigned char));
	rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, ntris, m_triareas);
	rcRasterizeTriangles(m_ctx, verts, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb);

	delete[] m_triareas;
	m_triareas = nullptr;

	rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);

	m_chf = rcAllocCompactHeightfield();
	if (!m_chf) return -4;
	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf)) return -5;

	rcFreeHeightField(m_solid);
	m_solid = nullptr;

	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf)) return -6;

	if (!rcBuildDistanceField(m_ctx, *m_chf)) return -7;
	if (!rcBuildRegions(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea)) return -8;

	m_cset = rcAllocContourSet();
	if (!m_cset) return -9;
	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset)) return -10;

	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh) return -11;
	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh)) return -12;

	std::cout << "PMESH VERTS: " << m_pmesh->nverts << std::endl;

	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh) return -13;
	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh)) return -14;

	rcFreeCompactHeightfield(m_chf);
	m_chf = nullptr;
	rcFreeContourSet(m_cset);
	m_cset = nullptr;

	if (m_cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON) return -15;

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
	/*
	params.offMeshConVerts = m_geom->getOffMeshConnectionVerts();
	params.offMeshConRad = m_geom->getOffMeshConnectionRads();
	params.offMeshConDir = m_geom->getOffMeshConnectionDirs();
	params.offMeshConAreas = m_geom->getOffMeshConnectionAreas();
	params.offMeshConFlags = m_geom->getOffMeshConnectionFlags();
	params.offMeshConUserID = m_geom->getOffMeshConnectionId();
	params.offMeshConCount = m_geom->getOffMeshConnectionCount();
	*/
	params.walkableHeight = m_agentHeight;
	params.walkableRadius = m_agentRadius;
	params.walkableClimb = m_agentMaxClimb;
	rcVcopy(params.bmin, m_pmesh->bmin);
	rcVcopy(params.bmax, m_pmesh->bmax);
	params.cs = m_cfg.cs;
	params.ch = m_cfg.ch;
	params.buildBvTree = true;

	unsigned char* navData = nullptr;
	int navDataSize = 0;
	if (!dtCreateNavMeshData(&params, &navData, &navDataSize)) return -16;

	m_navMesh = dtAllocNavMesh();
	if (!m_navMesh) {
		dtFree(navData);
		return -17;
	}

	dtStatus status;
	status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
	if (dtStatusFailed(status)){
		dtFree(navData);
		return -18;
	}

	status = m_navQuery->init(m_navMesh, 2048);
	if (dtStatusFailed(status)) return -19;

	return 1;
}

//test functions

DLLEXPORT double MA_NavMeshCreate(char* filename)
{
	return manav->createNavMesh(filename);
}

DLLEXPORT double MA_NavMeshDebugDraw()
{
	NavMeshDebugDraw DebugDraw;
	duDebugDrawNavMesh(&DebugDraw, *manav->m_navMesh, 0);
	return 1;
}