#pragma once

#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"

struct MANavigation {
	rcConfig m_cfg;

	rcContext* m_ctx;
	dtNavMeshQuery* m_navQuery;

	rcHeightfield* m_solid = nullptr;
	rcCompactHeightfield* m_chf = nullptr;
	rcContourSet* m_cset = nullptr;
	rcPolyMesh* m_pmesh = nullptr;
	rcPolyMeshDetail* m_dmesh = nullptr;	
	dtNavMesh* m_navMesh = nullptr;	
	unsigned char* m_triareas = nullptr;

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

	MANavigation();
	~MANavigation();
	void cleanup();
	int createNavMesh(char* filename);
	
};

extern MANavigation* manav;

