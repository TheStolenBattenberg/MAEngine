#include <MAE/Navigation/Navigation.h>
#include <MAE/Main.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <iostream>
#include <fstream>

// TODO: Get rid of this
struct MANavigation {
	std::vector<NavMesh::PathPoint> path;
	UnorderedVector<NavMesh*> navMeshes;
};

MANavigation manav;

DLLEXPORT double MA_NavMeshCreate() {
	TRYBEG();
	auto navmesh = new NavMesh();

	manav.navMeshes.add(navmesh);
	return ptrToDouble(navmesh);
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshDestroy(double navmesh) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	ptr->waitForBuild();

	manav.navMeshes.remove(ptr);
	delete ptr;

	return 1;
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshClear(double navmesh) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	ptr->cleanup();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshBeginBuild(double navmesh, double minx, double miny, double minz, double maxx, double maxy, double maxz) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->beginBuild((float)minx, (float)miny, (float)minz, (float)maxx, (float)maxy, (float)maxz);
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshEndBuild(double navmesh, double async) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->endBuild(async > 0.5);
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshWaitForBuild(double navmesh) {
	TRYBEG();
	return doubleToPtr<NavMesh>(navmesh)->waitForBuild();
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshGetBuildStatus(double navmesh) {
	TRYBEG();
	return doubleToPtr<NavMesh>(navmesh)->getBuildStatus();
	TRYEND(0);
}

// TODO: Remove this once we have a better way to load mesh data
std::vector<float> vertices;
std::vector<int> triangles;
DLLEXPORT double MA_NavMeshAddGMModel(double navmesh, char* filename) {
	TRYBEG();
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
	else return -1;

	float* verts = vertices.data();
	int nverts = vertices.size() / 3;
	int* tris = triangles.data();
	int ntris = triangles.size() / 3;

	return ptr->addMesh(verts, nverts, tris, ntris, matStack.data());
	TRYEND(-1);
}

int G_nverts = 0, G_ntris = 0;
DLLEXPORT double MA_NavSetVertexBufferSize(double nverts, double ntris) {
	TRYBEG();
	G_nverts = (int)nverts;
	G_ntris = (int)ntris;
	return 1;
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshAddVertexBuffer(double navmesh, float* verts, int* tris) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	return ptr->addMesh(verts, G_nverts, tris, G_ntris, matStack.data());
	TRYEND(-1);
}

DLLEXPORT double MA_NavMeshAddLink(double navmesh, double x1, double y1, double z1, double x2, double y2, double z2, double dir, double radius) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() == 0) return -1;

	float v1[3] = { (float)x1, (float)y1, (float)z1 };
	float v2[3] = { (float)x2, (float)y2, (float)z2 };
	return ptr->addLink(v1, v2, (int)dir, (float)radius);
	TRYEND(-1);
}

DLLEXPORT double MA_NavMeshDebugDraw(double navmesh) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);

	if (ptr->getBuildStatus() <= 0) return -1;

	ptr->debugDraw(renderer);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshSetAgentConfig(double navmesh, double agent_height, double agent_radius, double agent_max_climb, double agent_max_slope) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	ptr->agentHeight = (float)agent_height;
	ptr->agentRadius = (float)agent_radius;
	ptr->agentMaxClimb = (float)agent_max_climb;
	ptr->agentMaxSlope = (float)agent_max_slope;
	return 1;
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshSetConfig(double navmesh, double cell_size, double cell_height, double region_min_size, double region_merge_size, double edge_max_len, double edge_max_error, double verts_per_poly, double detail_sample_dist, double detail_sample_max_error) {
	TRYBEG();
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
	TRYEND(0);
}

DLLEXPORT double MA_NavMeshFindPath(double navmesh, double xf, double yf, double zf, double xt, double yt, double zt, double checkSize) {
	TRYBEG();
	auto ptr = doubleToPtr<NavMesh>(navmesh);
	if (ptr->getBuildStatus() <= 0) return -1;

	float start[3] = { (float)-xf, (float)zf, (float)yf };
	float end[3] = { (float)-xt, (float)zt, (float)yt };
	float extents[3] = { (float)checkSize, (float)checkSize, (float)checkSize };

	manav.path = ptr->findPath(start, end, extents);

	return manav.path.size();
	TRYEND(-1);
}

DLLEXPORT double MA_NavGetPathPoint(double point, double n) {
	TRYBEG();
	switch ((int)n)
	{
	case 0:
		return manav.path[(int)point].x;
	case 1:
		return manav.path[(int)point].y;
	case 2:
		return manav.path[(int)point].z;
	}
	return 0;
	TRYEND(0);
}
