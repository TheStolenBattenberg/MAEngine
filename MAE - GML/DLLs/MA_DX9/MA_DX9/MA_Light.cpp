#include "Main.h"
#include "Types.h"
#include "Utils.h"

DLLEXPORT double MADX9_LightCreate(double LightType)
{
	D3DLIGHTTYPE lightTable[] = {D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL};

	if ((uint) LightType > sizeof(lightTable) / sizeof(*lightTable))
		return ErrorInv;

	D3DLIGHT9* light = (D3DLIGHT9*) memset(new D3DLIGHT9, 0, sizeof(D3DLIGHT9));

	light->Type = lightTable[(uint) LightType];

	return putInto(light, mamain->Light);
}

DLLEXPORT double MADX9_LightDestroy(double index)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	delete mamain->Light[(uint) index];
	mamain->Light[(uint) index] = 0;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Attenuation0 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Attenuation1 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Attenuation2 = (float) att;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Direction = D3DXVECTOR3((float) dx, (float) dy, (float) dz);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Falloff = (float) falloff;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Phi = D3DXToRadian((float) phi);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Range = (float) range;

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	if (!isValidIndex((uint) index, mamain->Light))
		return ErrorInv;

	mamain->Light[(uint) index]->Theta = D3DXToRadian((float) theta);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightEnable(double index, double lightIndex)
{
	if (!isValidIndex((uint) lightIndex, mamain->Light))
		return ErrorInv;

	mamain->d3ddev->SetLight((uint) index, mamain->Light[(uint) lightIndex]);
	mamain->d3ddev->LightEnable((uint) index, 1);

	return ErrorOk;
}

DLLEXPORT double MADX9_LightDisable(double index) {
	mamain->d3ddev->LightEnable((uint) index, 0);

	return ErrorOk;
}
