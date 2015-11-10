#include "Main.h"
#include "Types.h"

DLLEXPORT double MADX9_MaterialCreate()
{
	D3DMATERIAL9 Material;
	ZeroMemory(&Material, sizeof(Material));

	for (uint i = 0; i < mamain.Material.size(); ++i)
	{
		if (mamain.Material[i].Power == -1.0f)
		{
			mamain.Material[i] = Material;
			return i;
		}
	}

	mamain.Material.push_back(Material);
	return mamain.Material.size() - 1;
}

DLLEXPORT double MADX9_MaterialDestroy(double index)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	//Find a better way to 'destroy' materials. Maybe a new resource type with a bool? Same for lights.
	mamain.Material[(uint)index].Power = -1.0f;

	return 1;
}

DLLEXPORT double MADX9_MaterialSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Diffuse = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Ambient = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Specular = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecularPower(double index, double p)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Power = (float)p;
	return 1;
}

DLLEXPORT double MADX9_MaterialSetEmissive(double index, double r, double g, double b, double a)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.Material[(uint)index].Emissive = D3DXCOLOR((float)r, (float)g, (float)b, (float)a);
	return 1;
}

DLLEXPORT double MADX9_MaterialSet(double index)
{
	if ((uint)index >= mamain.Material.size())
		return 0;

	if (mamain.Material[(uint)index].Power == -1.0f)
		return 0;

	mamain.d3ddev->SetMaterial(&mamain.Material[(uint)index]);
	return 1;
}