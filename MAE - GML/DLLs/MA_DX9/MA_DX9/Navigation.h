#pragma once

#include "Recast.h"

struct MANavigation {
	rcConfig m_cfg;

	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcPolyMeshDetail* m_dmesh;
	rcContext* m_ctx;

	MANavigation();
};

extern MANavigation* manav;
