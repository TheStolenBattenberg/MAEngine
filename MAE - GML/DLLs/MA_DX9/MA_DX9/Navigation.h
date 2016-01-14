#pragma once

#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"
#include "NavMeshDebugDraw.h"
#include <stdint.h>
#include <vector>
#include <thread>

class MANavMesh {
private:
	struct Mesh {
		float* verts;
		int nverts;
		int* tris;
		int ntris;
		D3DXMATRIX matrix;
	};

	std::vector<Mesh> m_meshes;

	std::vector<float> m_connection_verts;
	std::vector<float> m_connection_rad;
	std::vector<uint8_t> m_connection_dir;
	std::vector<uint8_t> m_connection_areas;
	std::vector<uint16_t> m_connection_flags;
	std::vector<uint32_t> m_connection_userIDs;

	std::thread m_build_thread;
	volatile int buildStatus = -20;

	void build();

public:
	rcContext* m_ctx;
	rcConfig m_cfg;
	dtNavMeshQuery* m_navQuery;
	dtQueryFilter m_filter;
	rcHeightfield* m_solid = nullptr;
	rcCompactHeightfield* m_chf = nullptr;
	rcContourSet* m_cset = nullptr;
	rcPolyMesh* m_pmesh = nullptr;
	rcPolyMeshDetail* m_dmesh = nullptr;
	dtNavMesh* m_navMesh = nullptr;
	uint8_t* m_triareas = nullptr;

	float m_cellSize;
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;

	MANavMesh();
	~MANavMesh();
	void cleanup();
	int beginBuild(float minx, float miny, float minz, float maxx, float maxy, float maxz);
	int addMesh(float* verts, int nverts, int* tris, int ntris, float* matrix);
	int endBuild(bool async);
	bool addLink(float* v1, float* v2, int dir, float radius);
	inline int getBuildStatus() { return buildStatus; }
	inline int waitForBuild() {
		if(m_build_thread.joinable()) m_build_thread.join();
		return buildStatus;
	}
};

struct MANavigation {
	NavMeshDebugDraw m_debugDraw;	
	float returnVec[3];
	
	dtPolyRef m_startRef;
	dtPolyRef m_endRef;
	static const int MAX_POLYS = 256;
	dtPolyRef m_polys[MAX_POLYS];
	int m_npolys;
	float m_straightPath[MAX_POLYS * 3];
	unsigned char m_straightPathFlags[MAX_POLYS];
	dtPolyRef m_straightPathPolys[MAX_POLYS];
	int m_nstraightPath = 0;

	std::vector<MANavMesh*> NavMeshes;

	MANavigation() {};
	~MANavigation();
};

extern MANavigation* manav;
