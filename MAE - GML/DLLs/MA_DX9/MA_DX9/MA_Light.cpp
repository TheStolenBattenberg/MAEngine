#include "Main.h"
#include "Types.h"

DLLEXPORT double MADX9_LightCreate(double LightType)
{
	D3DLIGHT9* light = new D3DLIGHT9;

	memset(light, 0, sizeof(*light));

	switch ((uint) LightType)
	{
	case 0:
		light->Type = D3DLIGHT_POINT;
		break;
	case 1:
		light->Type = D3DLIGHT_SPOT;
		break;
	case 2:
		light->Type = D3DLIGHT_DIRECTIONAL;
		break;
	default:
		return -1;
	}

	for (uint i = 0; i < mamain->Light.size(); ++i)
	{
		if (mamain->Light[i] == 0)
		{
			mamain->Light[i] = light;
			return i;
		}
	}

	mamain->Light.push_back(light);
	return mamain->Light.size() - 1;
}

DLLEXPORT double MADX9_LightDestroy(double index)
{
	if ((uint)index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint)index] == 0)
		return 0;

	delete mamain->Light[(uint) index];
	mamain->Light[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_LightSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation0(double index, double att)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Attenuation0 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation1(double index, double att)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Attenuation1 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetAttenuation2(double index, double att)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Attenuation2 = (float) att;

	return 1;
}

DLLEXPORT double MADX9_LightSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetDirection(double index, double dx, double dy, double dz)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Direction = D3DXVECTOR3((float) dx, (float) dy, (float) dz);

	return 1;
}

DLLEXPORT double MADX9_LightSetFalloff(double index, double falloff)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Falloff = (float) falloff;

	return 1;
}

DLLEXPORT double MADX9_LightSetPhi(double index, double phi)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Phi = D3DXToRadian((float) phi);

	return 1;
}

DLLEXPORT double MADX9_LightSetPosition(double index, double x, double y, double z)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Position = D3DXVECTOR3((float) x, (float) y, (float) z);

	return 1;
}

DLLEXPORT double MADX9_LightSetRange(double index, double range)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Range = (float) range;

	return 1;
}

DLLEXPORT double MADX9_LightSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_LightSetTheta(double index, double theta)
{
	if ((uint) index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) index] == 0)
		return 0;

	mamain->Light[(uint) index]->Theta = D3DXToRadian((float) theta);

	return 1;
}

DLLEXPORT double MADX9_LightEnable(double Index, double LightIndex)
{
	if ((uint) Index >= mamain->Light.size())
		return 0;

	if (mamain->Light[(uint) Index] == 0)
		return 0;

	mamain->d3ddev->SetLight((DWORD) Index, mamain->Light[(uint) LightIndex]);
	mamain->d3ddev->LightEnable((DWORD) Index, TRUE);

	return 1;
}

DLLEXPORT double MADX9_LightDisable(double Index) {
	mamain->d3ddev->LightEnable((DWORD) Index, FALSE);

	return 1;
}
