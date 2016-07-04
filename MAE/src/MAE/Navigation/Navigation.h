#pragma once

#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"
#include <MAE/Navigation/NavMeshDebugDraw.h>
#include <stdint.h>
#include <vector>
#include <thread>
#include <MAE/Core/UnorderedVector.h>

class NavMesh {
private:
	struct Mesh {
		float* verts;
		int nverts;
		int* tris;
		int ntris;
		D3DXMATRIX matrix;
	};

	std::vector<Mesh> meshes;

	struct Connection {
		float v1[3];
		float v2[3];
		float rad;
		uint8_t dir;
		uint8_t area;
		uint16_t flag;
		uint32_t userID;
	};
	std::vector<Connection> connections;

	std::thread buildThread;
	volatile int buildStatus = -20;

	void build();

public:
	rcContext* context;
	rcConfig config;
	dtNavMeshQuery* navQuery;
	dtQueryFilter queryFilter;
	rcHeightfield* heightfield = nullptr;
	rcCompactHeightfield* compactHeightfield = nullptr;
	rcContourSet* contourSet = nullptr;
	rcPolyMesh* polyMesh = nullptr;
	rcPolyMeshDetail* detailMesh = nullptr;
	dtNavMesh* navMesh = nullptr;
	uint8_t* triAreas = nullptr;

	float cellSize;
	float cellHeight;
	float agentHeight;
	float agentRadius;
	float agentMaxClimb;
	float agentMaxSlope;
	float regionMinSize;
	float regionMergeSize;
	float edgeMaxLen;
	float edgeMaxError;
	float vertsPerPoly;
	float detailSampleDist;
	float detailSampleMaxError;

	NavMesh();
	~NavMesh();
	void cleanup();
	int beginBuild(float minx, float miny, float minz, float maxx, float maxy, float maxz);
	int addMesh(float* verts, int nverts, int* tris, int ntris, float* matrix);
	int endBuild(bool async);
	bool addLink(float* v1, float* v2, int dir, float radius);
	inline int getBuildStatus() { return buildStatus; }
	inline int waitForBuild() {
		if(buildThread.joinable()) buildThread.join();
		return buildStatus;
	}
};

struct MANavigation {
	NavMeshDebugDraw debugDraw;	

	static const int MAX_POLYS = 256;
	dtPolyRef polys[MAX_POLYS];
	int numPolys;
	float straightPath[MAX_POLYS * 3];
	unsigned char straightPathFlags[MAX_POLYS];
	dtPolyRef straightPathPolys[MAX_POLYS];
	int numPathPoints = 0;

	UnorderedVector<NavMesh*> navMeshes;

	MANavigation() {};
	~MANavigation();
};

extern MANavigation manav;
