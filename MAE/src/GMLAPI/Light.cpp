#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_LightCreate(double LightType)
{
	D3DLIGHTTYPE lightTable[] = {D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL};

	if ((uint) LightType > sizeof(lightTable) / sizeof(*lightTable))
		return ErrorInv;

	D3DLIGHT9* light = (D3DLIGHT9*) memset(new D3DLIGHT9, 0, sizeof(D3DLIGHT9));

	light->Type = lightTable[(uint) LightType];

	mamain->Light.add(light);

	return ptrToDouble(light);
}

DLLEXPORT double MADX9_LightDestroy(double light)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	mamain->Light.remove(ptr);
	delete ptr;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAmbient(double light, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation0(double light, double att)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Attenuation0 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation1(double light, double att)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Attenuation1 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation2(double light, double att)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Attenuation2 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetDiffuse(double light, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetDirection(double light, double dx, double dy, double dz)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Direction = D3DXVECTOR3((float) dx, (float) dy, (float) dz);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetFalloff(double light, double falloff)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Falloff = (float) falloff;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetPhi(double light, double phi)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Phi = D3DXToRadian((float) phi);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetPosition(double light, double x, double y, double z)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetRange(double light, double range)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Range = (float) range;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetSpecular(double light, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetTheta(double light, double theta)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(light);

	ptr->Theta = D3DXToRadian((float) theta);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightEnable(double index, double lightIndex)
{
	auto ptr = doubleToPtr<D3DLIGHT9>(lightIndex);

	mamain->d3ddev->SetLight((uint) index, ptr);
	mamain->d3ddev->LightEnable((uint) index, 1);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightDisable(double index) {
	mamain->d3ddev->LightEnable((uint) index, 0);

	return ErrorOk;
}
