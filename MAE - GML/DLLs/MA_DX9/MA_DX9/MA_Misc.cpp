#include "Main.h"
#include "Types.h"

/**
 * Errors
 */

DLLEXPORT double MADX9_ErrorSetFlags(double flags) {
	mamain->err.flags = (uint)flags;

	return 1;
}

DLLEXPORT double MADX9_ErrorEmpty() {
	return mamain->err.empty();
}

DLLEXPORT const char* MADX9_ErrorPop() {
	return mamain->returnStr(mamain->err.pop());
}

/**
 * Hook
 */

DLLEXPORT double MADX9_HookEnable(double actions)
{
	return mamain->hook->enable((Hook::Actions) (uint) actions);
}

DLLEXPORT double MADX9_HookDisable(double actions)
{
	mamain->hook->disable((Hook::Actions) (uint) actions);

	return 1;
}

DLLEXPORT double MADX9_HookStackPopPointer(double ind)
{
	if (!mamain->hook->values.empty())
	{
		double p = 0.0;

		*((void**) &p) = mamain->hook->values.top().getPointer();
		mamain->hook->values.pop();

		return p;
	}

	return -1;
}

DLLEXPORT double MADX9_HookStackEmpty(double ind)
{
	return mamain->hook->values.empty();
}

DLLEXPORT double MADX9_HookStackClear(double ind)
{
	while (!mamain->hook->values.empty())
		mamain->hook->values.pop();

	return 1;
}

DLLEXPORT double MADX9_HookSetPropertyNull(double prop)
{
	return mamain->hook->set((Hook::Propertys) (uint) prop, Variant());
}

DLLEXPORT double MADX9_HookSetPropertyInt(double prop, double value)
{
	return mamain->hook->set((Hook::Propertys) (uint) prop, Variant((int) value));
}

DLLEXPORT double MADX9_HookSetPropertyPointer(double prop, double value)
{
	return mamain->hook->set((Hook::Propertys) (uint) prop, Variant(*(void**) &value));
}

/**
 * States
 */

DLLEXPORT double MADX9_SetSamplerState(double stage, double type, double value)
{
	return SUCCEEDED(mamain->d3ddev->SetSamplerState((uint)stage, (D3DSAMPLERSTATETYPE)(uint)type, (uint)value));
}

DLLEXPORT double MADX9_SetRenderState(double state, double value)
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

	return SUCCEEDED(mamain->d3ddev->SetRenderState((D3DRENDERSTATETYPE)(uint)state, v));
}

/**
 * Misc :D
 */

DLLEXPORT double MADX9_FreePointer(double p)
{
	if (*(LPUNKNOWN*) &p == 0)
		return 0;

	return SUCCEEDED((*(LPUNKNOWN*) &p)->Release());
}

DLLEXPORT double MADX9_Clear(double colour, double alpha, double z, double stencil, double flags)
{
	uint c = (uint) colour;

	return SUCCEEDED(mamain->d3ddev->Clear(0, 0, (uint) flags, D3DCOLOR_ARGB((uint) (alpha * 255.0), c, c >> 8, c >> 16), (float) z, (DWORD) stencil));
}

DLLEXPORT double MADX9_IsNullPointer(double p)
{
	return *(void**) &p == 0;
}
