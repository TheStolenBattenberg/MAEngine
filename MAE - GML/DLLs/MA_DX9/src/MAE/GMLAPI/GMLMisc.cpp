#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Math.h>
#include <MAE/Core/Utils.h>

#include <MAE/GMLAPI/GMLMain.h>

std::string retStr;

/**
 * Math. (Remove, just for debugging)
 */
DLLEXPORT double MADX9_MathCosineInterp(double x, double y, double s) {
	return (double)interpCosine((float)x, (float)y, (float)s);
}

DLLEXPORT double MADX9_MathRandomRange(double min, double max) {
	return (double)interpLinear((float)min, (float)max, (float) rand() / RAND_MAX);
}

/**
 * States
 */

DLLEXPORT double MADX9_SetSamplerState(double stage, double type, double value)
{
	HRESULT res = mamain->d3ddev->SetSamplerState((uint) stage, (D3DSAMPLERSTATETYPE) (uint) type, (uint) value);

	if (FAILED(res))
		return mamain->setError(ErrorD3D9);

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
		return mamain->setError(ErrorD3D9);

	return ErrorOk;
}

/**
 * Misc :D
 */

DLLEXPORT double MADX9_FreePointer(double p)
{
	LPUNKNOWN ptr = (LPUNKNOWN) DoubleToPtr(p);

	if (ptr == 0)
		return mamain->setError(ErrorInv);

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
