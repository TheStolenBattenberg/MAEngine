#pragma once

#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"
#include <vector>
#include <thread>
#include <MAE/Core/Types.h>
#include <MAE/Navigation/NavMeshDebugDraw.h>

//TODO: Use a vector type instead of passing float* everywhere

class NavMesh {
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
		ubyte dir;
		ubyte area;
		ushort flag;
		uint userID;
	};
	std::vector<Connection> connections;

	std::thread buildThread;
	volatile int buildStatus = -20;

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
	ubyte* triAreas = nullptr;

	void build();

public:
	struct PathPoint {
		float x, y, z;
		uint polyRef;
	};

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
	void debugDraw();
	std::vector<PathPoint> findPath(float* start, float* end, float* checkExtents);
	inline int getBuildStatus() {
		return buildStatus;
	}
	inline int waitForBuild() {
		if(buildThread.joinable()) buildThread.join();
		return buildStatus;
	}
};

