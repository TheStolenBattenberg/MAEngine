#include "Navigation.h"
#include "Main.h"
#include "DetourDebugDraw.h"
#include "RecastDebugDraw.h"
#include <iostream>

MANavigation* manav = nullptr;

MANavigation::MANavigation()
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

int MANavigation::createNavMesh(char* filename, float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
	//free previous navmesh
	cleanup();

	/*
		Load test mesh from GM model file.
		This function should take in a vertex buffer instead.
	*/
	std::string line;
	std::ifstream file(filename);
	vertices.clear();
	triangles.clear();
	normals.clear();
	if (file){
		int version, lines;
		file >> version >> lines;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (int i = 0; i < lines; i++){
			int n;
			file >> n;
			if (n == 6){
				float x, y, z;
				file >> x >> y >> z;
				float nx, ny, nz;
				file >> nx >> ny >> nz;

				triangles.push_back(vertices.size() / 3);

				vertices.push_back(-x);
				vertices.push_back(z);
				vertices.push_back(y);

				normals.push_back(nx);
				normals.push_back(ny);
				normals.push_back(nz);
			}
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		file.close();
	}
	else return 0;

	float* verts = &vertices[0];
	int nverts = vertices.size() / 3;
	int* tris = &triangles[0];
	int ntris = triangles.size() / 3;

	float bmin[3] = { minx, miny, minz };
	float bmax[3] = { maxx, maxy, maxz };

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

	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh) return -13;
	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh)) return -14;

	rcFreeCompactHeightfield(m_chf);
	m_chf = nullptr;
	rcFreeContourSet(m_cset);
	m_cset = nullptr;

	if (m_cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON) return -15;

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
	/*
	params.offMeshConVerts = 
	params.offMeshConRad = 
	params.offMeshConDir = 
	params.offMeshConAreas = 
	params.offMeshConFlags = 
	params.offMeshConUserID = 
	params.offMeshConCount = 
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
	return manav->createNavMesh(filename, -30, -30, -30, 30, 30, 30);
}

DLLEXPORT double MA_NavMeshDestroy()
{
	manav->cleanup();
	return 1;
}

DLLEXPORT double MA_NavMeshDebugDraw()
{
	duDebugDrawNavMesh(&manav->m_debugDraw, *manav->m_navMesh, 0);
	float* bmin = manav->m_cfg.bmin;
	float* bmax = manav->m_cfg.bmax;
	duDebugDrawBoxWire(&manav->m_debugDraw, bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2], duRGBA(255, 255, 255, 128), 1.f);
	/*
	float* verts = &manav->vertices[0];
	int nverts = manav->vertices.size() / 3;
	int* tris = &manav->triangles[0];
	int ntris = manav->triangles.size() / 3;
	float* normals = &manav->normals[0];
	duDebugDrawTriMesh(&manav->m_debugDraw, verts, nverts, tris, normals, ntris, 0, 1.f);
	*/
	return 1;
}

DLLEXPORT double MA_NavMeshSetAgentConfig(double agent_height, double agent_radius, double agent_max_climb, double agent_max_slope)
{
	manav->m_agentHeight = (float)agent_height;
	manav->m_agentRadius = (float)agent_radius;
	manav->m_agentMaxClimb = (float)agent_max_climb;
	manav->m_agentMaxSlope = (float)agent_max_slope;
	return 1;
}

DLLEXPORT double MA_NavMeshSetConfig(double cell_size, double cell_height, double region_min_size, double region_merge_size, double edge_max_len,
									 double edge_max_error, double verts_per_poly, double detail_sample_dist, double detail_sample_max_error)
{
	manav->m_cellSize = (float)cell_size;
	manav->m_cellHeight = (float)cell_height;	
	manav->m_regionMinSize = (float)region_min_size;
	manav->m_regionMergeSize = (float)region_merge_size;
	manav->m_edgeMaxLen = (float)edge_max_len;
	manav->m_edgeMaxError = (float)edge_max_error;
	manav->m_vertsPerPoly = (float)verts_per_poly;
	manav->m_detailSampleDist = (float)detail_sample_dist;
	manav->m_detailSampleMaxError = (float)detail_sample_max_error;
	return 1;
}

DLLEXPORT double MA_NavFindNearestPoly(double x, double y, double z, double ex, double ey, double ez)
{
	float pos[3] = { (float)-x, (float)z, (float)y };
	float extents[3] = { (float)ex, (float)ez, (float)ey };
	dtPolyRef ref;
	manav->m_navQuery->findNearestPoly(pos, extents, &manav->m_filter, &ref, 0);
	return ref;
}

/*
DLLEXPORT double MA_NavFindPath(double start_poly, double end_poly, double xf, double yf, double zf, double xt, double yt, double zt)
{
	dtPolyRef startRef = (dtPolyRef)start_poly;
	dtPolyRef endRef = (dtPolyRef)end_poly;
	float startPos[3] = { xf, yf, zf };
	float endPos[3] = { xt, yt, zt };
	manav->m_navQuery->findPath(startRef, endRef, startPos, endPos, &manav->m_filter, manav->m_polys, &manav->m_npolys, MANavigation::MAX_POLYS);
	return manav->m_npolys;
}
*/
DLLEXPORT double MA_NavGetPoly(double n)
{
	return manav->m_polys[(int)n];
}

DLLEXPORT double MA_NavFindStraightPath(double start_poly, double end_poly, double xf, double yf, double zf, double xt, double yt, double zt)
{
	dtPolyRef startRef = (dtPolyRef)start_poly;
	dtPolyRef endRef = (dtPolyRef)end_poly;
	float startPos[3] = { (float)-xf, (float)zf, (float)yf };
	float endPos[3] = { (float)-xt, (float)zt, (float)yt };
	float epos[3];

	manav->m_navQuery->findPath(startRef, endRef, startPos, endPos, &manav->m_filter, manav->m_polys, &manav->m_npolys, MANavigation::MAX_POLYS);

	rcVcopy(epos, endPos);
	if (manav->m_polys[manav->m_npolys - 1] != endRef)
		manav->m_navQuery->closestPointOnPoly(manav->m_polys[manav->m_npolys - 1], endPos, epos, 0);

	if (manav->m_npolys) {
		manav->m_navQuery->findStraightPath(startPos, epos, manav->m_polys, manav->m_npolys, manav->m_straightPath, manav->m_straightPathFlags,
			manav->m_straightPathPolys, &manav->m_nstraightPath, MANavigation::MAX_POLYS, 0);
	}

	return manav->m_npolys;
	
}

DLLEXPORT double MA_NavGetPathLength()
{
	return manav->m_nstraightPath;
}

DLLEXPORT double MA_NavGetPathPos(double n)
{
	manav->returnVec[0] = manav->m_straightPath[(int)n * 3] * -1;
	manav->returnVec[1] = manav->m_straightPath[(int)n * 3 + 2];
	manav->returnVec[2] = manav->m_straightPath[(int)n * 3 + 1];
	return 1;
}

DLLEXPORT double MA_NavGetVec(double n)
{
	switch ((int)n)
	{
	case 0:
		return manav->returnVec[0];
	case 1:
		return manav->returnVec[1];
	case 2:
		return manav->returnVec[2];
	}
	return 0;
}
