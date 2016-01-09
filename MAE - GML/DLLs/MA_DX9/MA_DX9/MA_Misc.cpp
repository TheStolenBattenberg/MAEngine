#include "Main.h"
#include "Types.h"
#include "Hook.h"
#include "Math.h"
#include "Utils.h"

/**
 * Math. (Remove, just for debugging)
 */
DLLEXPORT double MADX9_MathCosineInterp(double x, double y, double s) {
	return (double)interpCosine((float)x, (float)y, (float)s);
}

DLLEXPORT double MADX9_MathRandomRange(double min, double max) {
	return (double)randomRangef((float)min, (float)max);
}

/**
 * Errors
 */

DLLEXPORT double MADX9_ErrorSetFlags(double flags) {
	mamain->errCrit.flags = (uint)flags;

	return 1;
}

DLLEXPORT double MADX9_ErrorEmpty() {
	return mamain->errCrit.empty();
}

DLLEXPORT const char* MADX9_ErrorPop() {
	return mamain->returnStr(mamain->errCrit.pop().getErrorString());
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
	HRESULT res = mamain->d3ddev->SetSamplerState((uint) stage, (D3DSAMPLERSTATETYPE) (uint) type, (uint) value);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetSamplerState");

	return ErrorOk;
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

	HRESULT res = mamain->d3ddev->SetRenderState((D3DRENDERSTATETYPE) (uint) state, v);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetSamplerState");

	return ErrorOk;
}

/**
 * Misc :D
 */

DLLEXPORT double MADX9_FreePointer(double p)
{
	LPUNKNOWN ptr = (LPUNKNOWN) DoubleToPtr(p);

	if (ptr == 0)
		return ErrorHandle(mamain->err, ErrorInv);

	ptr->Release();

	return ErrorOk;
}

DLLEXPORT double MADX9_Clear(double colour, double alpha, double z, double stencil, double flags)
{
	uint c = (uint) colour;

	return SUCCEEDED(mamain->d3ddev->Clear(0, 0, (uint) flags, D3DCOLOR_ARGB((uint) (alpha * 255.0), c, c >> 8, c >> 16), (float) z, (uint) stencil));
}

DLLEXPORT double MADX9_IsNullPointer(double p)
{
	return DoubleToPtr(p) == 0;
}
