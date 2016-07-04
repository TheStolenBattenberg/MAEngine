#include <MAE/Navigation/Navigation.h>
#include <DetourDebugDraw.h>
#include <MAE/Main.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MA_NavMeshCreate()
{
	auto navmesh = new NavMesh();

	manav.navMeshes.add(navmesh);
	return ptrToDouble(navmesh);
}

DLLEXPORT double MA_NavMeshDestroy(double navmesh)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	ptr->waitForBuild();

	manav.navMeshes.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MA_NavMeshClear(double navmesh)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	ptr->cleanup();
	return 1;
}

DLLEXPORT double MA_NavMeshBeginBuild(double navmesh, double minx, double miny, double minz, double maxx, double maxy, double maxz)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->beginBuild((float)minx, (float)miny, (float)minz, (float)maxx, (float)maxy, (float)maxz);
}

DLLEXPORT double MA_NavMeshEndBuild(double navmesh, double async)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->endBuild(async > 0.5);
}

DLLEXPORT double MA_NavMeshWaitForBuild(double navmesh)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	return ptr->waitForBuild();
}

DLLEXPORT double MA_NavMeshGetBuildStatus(double navmesh)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	return ptr->getBuildStatus();
}

// TODO: Remove this once we have a better way to load mesh data
std::vector<float> vertices;
std::vector<int> triangles;
DLLEXPORT double MA_NavMeshAddGMModel(double navmesh, char* filename)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	if (ptr->getBuildStatus() == 0) return -1;

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

	return ptr->addMesh(verts, nverts, tris, ntris, matStack.data());
}

int G_nverts = 0, G_ntris = 0;
DLLEXPORT double MA_NavSetVertexBufferSize(double nverts, double ntris)
{
	G_nverts = (int)nverts;
	G_ntris = (int)ntris;
	return 1;
}

DLLEXPORT double MA_NavMeshAddVertexBuffer(double navmesh, float* verts, int* tris)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->addMesh(verts, G_nverts, tris, G_ntris, matStack.data());
}

DLLEXPORT double MA_NavMeshAddLink(double navmesh, double x1, double y1, double z1, double x2, double y2, double z2, double dir, double radius)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	float v1[3] = { (float)x1, (float)y1, (float)z1 };
	float v2[3] = { (float)x2, (float)y2, (float)z2 };
	return ptr->addLink(v1, v2, (int)dir, (float)radius);
}

DLLEXPORT double MA_NavMeshDebugDraw(double navmesh)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() <= 0) return -1;

	duDebugDrawNavMesh(&manav.debugDraw, *ptr->navMesh, 0);
	float* bmin = ptr->config.bmin;
	float* bmax = ptr->config.bmax;
	duDebugDrawBoxWire(&manav.debugDraw, bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2], duRGBA(255, 255, 255, 128), 1.f);
	return 1;
}

DLLEXPORT double MA_NavMeshSetAgentConfig(double navmesh, double agent_height, double agent_radius, double agent_max_climb, double agent_max_slope)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	ptr->agentHeight = (float)agent_height;
	ptr->agentRadius = (float)agent_radius;
	ptr->agentMaxClimb = (float)agent_max_climb;
	ptr->agentMaxSlope = (float)agent_max_slope;
	return 1;
}

DLLEXPORT double MA_NavMeshSetConfig(double navmesh, double cell_size, double cell_height, double region_min_size, double region_merge_size,
	double edge_max_len, double edge_max_error, double verts_per_poly, double detail_sample_dist, double detail_sample_max_error)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	ptr->cellSize = (float)cell_size;
	ptr->cellHeight = (float)cell_height;
	ptr->regionMinSize = (float)region_min_size;
	ptr->regionMergeSize = (float)region_merge_size;
	ptr->edgeMaxLen = (float)edge_max_len;
	ptr->edgeMaxError = (float)edge_max_error;
	ptr->vertsPerPoly = (float)verts_per_poly;
	ptr->detailSampleDist = (float)detail_sample_dist;
	ptr->detailSampleMaxError = (float)detail_sample_max_error;
	return 1;
}

DLLEXPORT double MA_NavMeshFindNearestPoly(double navmesh, double x, double y, double z, double ex, double ey, double ez)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() <= 0) return -1;

	float pos[3] = { (float)-x, (float)z, (float)y };
	float extents[3] = { (float)ex, (float)ez, (float)ey };
	dtPolyRef ref;
	ptr->navQuery->findNearestPoly(pos, extents, &ptr->queryFilter, &ref, 0);
	return ref;
}

DLLEXPORT double MA_NavMeshFindPath(double navmesh, double start_poly, double end_poly, double xf, double yf, double zf, double xt, double yt, double zt)
{
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	if (ptr->getBuildStatus() <= 0) return -1;

	dtPolyRef startRef = (dtPolyRef)start_poly;
	dtPolyRef endRef = (dtPolyRef)end_poly;
	float startPos[3] = { (float)-xf, (float)zf, (float)yf };
	float endPos[3] = { (float)-xt, (float)zt, (float)yt };
	float epos[3];

	ptr->navQuery->findPath(startRef, endRef, startPos, endPos, &ptr->queryFilter, manav.polys, &manav.numPolys, MANavigation::MAX_POLYS);

	rcVcopy(epos, endPos);
	if (manav.polys[manav.numPolys - 1] != endRef)
		ptr->navQuery->closestPointOnPoly(manav.polys[manav.numPolys - 1], endPos, epos, 0);

	if (manav.numPolys) {
		ptr->navQuery->findStraightPath(startPos, epos, manav.polys, manav.numPolys, manav.straightPath, manav.straightPathFlags,
			manav.straightPathPolys, &manav.numPathPoints, MANavigation::MAX_POLYS, 0);
	}

	return manav.numPolys;
}

DLLEXPORT double MA_NavGetPoly(double n)
{
	return manav.polys[(int)n];
}

DLLEXPORT double MA_NavGetPathLength()
{
	return manav.numPathPoints;
}

float returnVec[3];
DLLEXPORT double MA_NavGetPathPoint(double n)
{
	returnVec[0] = manav.straightPath[(int)n * 3] * -1;
	returnVec[1] = manav.straightPath[(int)n * 3 + 2];
	returnVec[2] = manav.straightPath[(int)n * 3 + 1];
	return 1;
}

DLLEXPORT double MA_NavGetVec(double n)
{
	switch ((int)n)
	{
	case 0:
		return returnVec[0];
	case 1:
		return returnVec[1];
	case 2:
		return returnVec[2];
	}
	return 0;
}
