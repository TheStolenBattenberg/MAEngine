#include "Main.h"
#include "Types.h"
#include "Exception.h"
#include "Utils.h"

DLLEXPORT double MADX9_LightCreate(double LightType)
{
	_GMEXBEG();

	D3DLIGHTTYPE lightTable[] = {D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL};

	if ((uint) LightType > sizeof(lightTable) / sizeof(*lightTable))
		throw MAEInvException("Invalid light type");

	D3DLIGHT9* light = (D3DLIGHT9*) memset(new D3DLIGHT9, 0, sizeof(D3DLIGHT9));

	light->Type = lightTable[(uint) LightType];

	return putInto(light, mamain->Light);

	_GMEXEND(-1, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightDestroy(double index)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	delete mamain->Light[(uint) index];
	mamain->Light[(uint) index] = 0;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Attenuation0 = (float) att;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Attenuation1 = (float) att;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Attenuation2 = (float) att;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Direction = D3DXVECTOR3((float) dx, (float) dy, (float) dz);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Falloff = (float) falloff;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Phi = D3DXToRadian((float) phi);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Range = (float) range;

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	_GMEXBEG();

	if (!isValidIndex((uint) index, mamain->Light))
		throw MAEInvException("Invalid light index");

	mamain->Light[(uint) index]->Theta = D3DXToRadian((float) theta);

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightEnable(double index, double lightIndex)
{
	_GMEXBEG();

	if (!isValidIndex((uint) lightIndex, mamain->Light))
		throw MAEInvException("Invalid light index");

	CheckDX9Result(mamain->d3ddev->SetLight((uint) index, mamain->Light[(uint) lightIndex]), "Failed to enable light");
	CheckDX9Result(mamain->d3ddev->LightEnable((uint) index, 1), "Failed to enable light");

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}

DLLEXPORT double MADX9_LightDisable(double index) {
	_GMEXBEG();

	CheckDX9Result(mamain->d3ddev->LightEnable((uint) index, 0), "Failed to disable light");

	return 1;

	_GMEXEND(0, mamain->err, mamain->ignoreInv);
}
