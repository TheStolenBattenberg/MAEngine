#include "Main.h"
#include "Types.h"

/**
 * Errors
 */

DLLEXPORT double MADX9_ErrorSetFlags(double flags) {
	mamain.err.flags = (uint)flags;

	return 1;
}

DLLEXPORT double MADX9_ErrorEmpty() {
	return mamain.err.empty();
}

DLLEXPORT const char* MADX9_ErrorPop() {
	return mamain.returnStr(mamain.err.pop());
}

/**
 * Hook
 */

DLLEXPORT double MADX9_HookEnable(double actions)
{
	return mamain.hook->enable((D3DHook::Actions) (uint) actions);
}

DLLEXPORT double MADX9_HookDisable(double actions)
{
	mamain.hook->disable((D3DHook::Actions) (uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HookStackPopPointer(double ind)
{
	double p = 0.0;

	if (!mamain.hook->values.empty())
	{
		*((void**) &p) = mamain.hook->values.top().getPointer();
		mamain.hook->values.pop();
	}

	return p;
}

DLLEXPORT double MADX9_HookStackEmpty(double ind)
{
	return mamain.hook->values.empty();
}

DLLEXPORT double MADX9_HookStackClear(double ind)
{
	while (!mamain.hook->values.empty())
		mamain.hook->values.pop();

	return 1;
}

DLLEXPORT double MADX9_HookSetPropertyPointer(double prop, double value)
{
	return mamain.hook->set((D3DHook::Propertys) (uint) prop, Variant(*(void**) &value));
}

/**
 * States
 */

DLLEXPORT double MADX9_SamplerSetState(double stage, double type, double value)
{
	return SUCCEEDED(mamain.d3ddev->SetSamplerState((uint)stage, (D3DSAMPLERSTATETYPE)(uint)type, (uint)value));
}

DLLEXPORT double MADX9_RenderSetState(double state, double value)
{
	uint v;

	switch ((D3DRENDERSTATETYPE)(uint)state)
	{
	case D3DRS_FOGSTART:
	case D3DRS_FOGEND:
	case D3DRS_FOGDENSITY:
	case D3DRS_POINTSIZE:
	case D3DRS_POINTSIZE_MIN:
	case D3DRS_POINTSCALE_A:
	case D3DRS_POINTSCALE_B:
	case D3DRS_POINTSCALE_C:
	case D3DRS_PATCHEDGESTYLE:
	case D3DRS_POINTSIZE_MAX:
	case D3DRS_TWEENFACTOR:
	case D3DRS_DEPTHBIAS:
		*(float*)&v = (float)value;
		break;
	default:
		v = (uint)value;
		break;
	}

	return SUCCEEDED(mamain.d3ddev->SetRenderState((D3DRENDERSTATETYPE)(uint)state, v));
}

/**
 * Flush
 */

DLLEXPORT double MADX9_FlushBegin()
{
	mamain.flush->beginFetch();
	return 1;
}

DLLEXPORT double MADX9_FlushEnd()
{
	mamain.flush->endFetch();
	return 1;
}
