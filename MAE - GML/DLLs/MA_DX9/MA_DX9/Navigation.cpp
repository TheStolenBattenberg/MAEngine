#include "Navigation.h"
#include "Main.h"

MANavigation* manav = nullptr;

MANavigation::MANavigation()
{
	m_ctx = new rcContext();
}

DLLEXPORT double MA_NavmeshCreate(char* filename)
{
	memset(&manav->m_cfg, 0, sizeof(manav->m_cfg));
	manav->m_cfg.cs = 16.f;
	manav->m_cfg.ch = 16.f;
	manav->m_cfg.walkableSlopeAngle = 30.f;
	manav->m_cfg.walkableHeight = 4;
	manav->m_cfg.walkableClimb = 1;
	manav->m_cfg.walkableRadius = 0;
	manav->m_cfg.maxEdgeLen = 4;
	manav->m_cfg.maxSimplificationError = 5;
	manav->m_cfg.minRegionArea = 8;
	manav->m_cfg.mergeRegionArea = 5;
	manav->m_cfg.maxVertsPerPoly = 6;
	manav->m_cfg.detailSampleDist = 0.f;
	manav->m_cfg.detailSampleMaxError = 2.f;

	manav->m_solid = rcAllocHeightfield();
	if (!manav->m_solid) return -1;

	if (!rcCreateHeightfield(manav->m_ctx, *manav->m_solid, manav->m_cfg.width, manav->m_cfg.height, manav->m_cfg.bmin, manav->m_cfg.bmax, manav->m_cfg.cs, manav->m_cfg.ch)) return -2;

	return 1;
}
