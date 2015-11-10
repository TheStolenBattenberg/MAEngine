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
 * Hooks
 */
DLLEXPORT double MADX9_HooksCreate()
{
	for (uint i = 0; i < mamain.Hooks.size(); ++i)
	{
		if (mamain.Hooks[i] == 0)
		{
			mamain.Hooks[i] = new D3DHooks(mamain.d3ddev);
			return i;
		}
	}

	mamain.Hooks.push_back(new D3DHooks(mamain.d3ddev));
	return mamain.Hooks.size() - 1;
}

DLLEXPORT double MADX9_HooksDestroy(double ind)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	delete mamain.Hooks[(uint)ind];
	mamain.Hooks[(uint)ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_HooksApply(double ind, double actions)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	mamain.Hooks[(uint)ind]->apply((D3DHooksActions)(uint)actions);

	return 1;
}

DLLEXPORT double MADX9_HooksRemove(double ind, double actions)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	mamain.Hooks[(uint)ind]->remove((D3DHooksActions)(uint)actions);

	return 1;
}

DLLEXPORT double MADX9_HooksMakeCurrent(double ind)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	mamain.Hooks[(uint)ind]->makeCurrent();

	return 1;
}

DLLEXPORT double MADX9_HooksStackPopPointer(double ind)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	double p;

	memset(&p, 0, sizeof(p));

	if (!mamain.Hooks[(uint)ind]->values.empty())
	{
		*((void**)&p) = mamain.Hooks[(uint)ind]->values.top().getPointer();
		mamain.Hooks[(uint)ind]->values.pop();
	}

	return p;
}

DLLEXPORT double MADX9_HooksStackEmpty(double ind)
{
	if ((uint)ind >= mamain.Hooks.size())
		return -1;

	if (mamain.Hooks[(uint)ind] == 0)
		return -1;

	return mamain.Hooks[(uint)ind]->values.empty();
}

DLLEXPORT double MADX9_HooksStackClear(double ind)
{
	if ((uint)ind >= mamain.Hooks.size())
		return 0;

	if (mamain.Hooks[(uint)ind] == 0)
		return 0;

	while (!mamain.Hooks[(uint)ind]->values.empty())
		mamain.Hooks[(uint)ind]->values.pop();

	return 1;
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