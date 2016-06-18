#include <MAE/Navigation/Navigation.h>
#include <DetourDebugDraw.h>
#include <MAE/Main.h>
#include <MAE/Core/Utils.h>

#include <MAE/GMLAPI/GMLMain.h>

DLLEXPORT double MA_NavMeshCreate()
{
	MANavMesh* navmesh = new MANavMesh();
	return putInto(navmesh, manav->NavMeshes);
}

DLLEXPORT double MA_NavMeshDestroy(double index)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	navmesh->waitForBuild();
	delete navmesh;
	manav->NavMeshes[(uint)index] = 0;
	return 1;
}

DLLEXPORT double MA_NavMeshClear(double index)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	navmesh->cleanup();
	return 1;
}

DLLEXPORT double MA_NavMeshBeginBuild(double index, double minx, double miny, double minz, double maxx, double maxy, double maxz)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	return navmesh->beginBuild((float)minx, (float)miny, (float)minz, (float)maxx, (float)maxy, (float)maxz);
}

DLLEXPORT double MA_NavMeshEndBuild(double index, double async)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	return navmesh->endBuild(async > 0.5);
}

DLLEXPORT double MA_NavMeshWaitForBuild(double index)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	return navmesh->waitForBuild();
}

DLLEXPORT double MA_NavMeshGetBuildStatus(double index)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	return navmesh->getBuildStatus();
}

std::vector<float> vertices;
std::vector<int> triangles;
DLLEXPORT double MA_NavMeshAddGMModel(double index, char* filename)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	std::string line;
	std::ifstream file(filename);
	vertices.clear();
	triangles.clear();
	if (file) {
		int version, lines;
		file >> version >> lines;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (int i = 0; i < lines; i++) {
			int n;
			file >> n;
			if (n > 1 && n < 10) {
				float x, y, z;
				file >> x >> y >> z;

				triangles.push_back(vertices.size() / 3);

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		file.close();
	}
	else return 0;

	float* verts = vertices.data();
	int nverts = vertices.size() / 3;
	int* tris = triangles.data();
	int ntris = triangles.size() / 3;

	return navmesh->addMesh(verts, nverts, tris, ntris, matStack.data());
}

int G_nverts = 0, G_ntris = 0;
DLLEXPORT double MA_NavSetVertexBufferSize(double nverts, double ntris)
{
	G_nverts = (int)nverts;
	G_ntris = (int)ntris;
	return 1;
}

DLLEXPORT double MA_NavMeshAddVertexBuffer(double index, float* verts, int* tris)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	return navmesh->addMesh(verts, G_nverts, tris, G_ntris, matStack.data());
}

DLLEXPORT double MA_NavMeshAddLink(double index, double x1, double y1, double z1, double x2, double y2, double z2, double dir, double radius)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() == 0) return -1;

	float v1[3] = { (float)x1, (float)y1, (float)z1 };
	float v2[3] = { (float)x2, (float)y2, (float)z2 };
	return navmesh->addLink(v1, v2, (int)dir, (float)radius);
}

DLLEXPORT double MA_NavMeshDebugDraw(double index)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() <= 0) return -1;

	duDebugDrawNavMesh(&manav->m_debugDraw, *navmesh->m_navMesh, 0);
	float* bmin = navmesh->m_cfg.bmin;
	float* bmax = navmesh->m_cfg.bmax;
	duDebugDrawBoxWire(&manav->m_debugDraw, bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2], duRGBA(255, 255, 255, 128), 1.f);
	return 1;
}

DLLEXPORT double MA_NavMeshSetAgentConfig(double index, double agent_height, double agent_radius, double agent_max_climb, double agent_max_slope)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	navmesh->m_agentHeight = (float)agent_height;
	navmesh->m_agentRadius = (float)agent_radius;
	navmesh->m_agentMaxClimb = (float)agent_max_climb;
	navmesh->m_agentMaxSlope = (float)agent_max_slope;
	return 1;
}

DLLEXPORT double MA_NavMeshSetConfig(double index, double cell_size, double cell_height, double region_min_size, double region_merge_size,
	double edge_max_len, double edge_max_error, double verts_per_poly, double detail_sample_dist, double detail_sample_max_error)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	navmesh->m_cellSize = (float)cell_size;
	navmesh->m_cellHeight = (float)cell_height;
	navmesh->m_regionMinSize = (float)region_min_size;
	navmesh->m_regionMergeSize = (float)region_merge_size;
	navmesh->m_edgeMaxLen = (float)edge_max_len;
	navmesh->m_edgeMaxError = (float)edge_max_error;
	navmesh->m_vertsPerPoly = (float)verts_per_poly;
	navmesh->m_detailSampleDist = (float)detail_sample_dist;
	navmesh->m_detailSampleMaxError = (float)detail_sample_max_error;
	return 1;
}

DLLEXPORT double MA_NavMeshFindNearestPoly(double index, double x, double y, double z, double ex, double ey, double ez)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() <= 0) return -1;

	float pos[3] = { (float)-x, (float)z, (float)y };
	float extents[3] = { (float)ex, (float)ez, (float)ey };
	dtPolyRef ref;
	navmesh->m_navQuery->findNearestPoly(pos, extents, &navmesh->m_filter, &ref, 0);
	return ref;
}

DLLEXPORT double MA_NavMeshFindPath(double index, double start_poly, double end_poly, double xf, double yf, double zf, double xt, double yt, double zt)
{
	MANavMesh* navmesh = manav->NavMeshes[(uint)index];
	if (navmesh->getBuildStatus() <= 0) return -1;

	dtPolyRef startRef = (dtPolyRef)start_poly;
	dtPolyRef endRef = (dtPolyRef)end_poly;
	float startPos[3] = { (float)-xf, (float)zf, (float)yf };
	float endPos[3] = { (float)-xt, (float)zt, (float)yt };
	float epos[3];

	navmesh->m_navQuery->findPath(startRef, endRef, startPos, endPos, &navmesh->m_filter, manav->m_polys, &manav->m_npolys, MANavigation::MAX_POLYS);

	rcVcopy(epos, endPos);
	if (manav->m_polys[manav->m_npolys - 1] != endRef)
		navmesh->m_navQuery->closestPointOnPoly(manav->m_polys[manav->m_npolys - 1], endPos, epos, 0);

	if (manav->m_npolys) {
		navmesh->m_navQuery->findStraightPath(startPos, epos, manav->m_polys, manav->m_npolys, manav->m_straightPath, manav->m_straightPathFlags,
			manav->m_straightPathPolys, &manav->m_nstraightPath, MANavigation::MAX_POLYS, 0);
	}

	return manav->m_npolys;
}

DLLEXPORT double MA_NavGetPoly(double n)
{
	return manav->m_polys[(int)n];
}

DLLEXPORT double MA_NavGetPathLength()
{
	return manav->m_nstraightPath;
}

DLLEXPORT double MA_NavGetPathPoint(double n)
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
