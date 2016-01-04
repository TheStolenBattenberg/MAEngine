#include "Main.h"
#include "Types.h"
#include "Exception.h"
#include "Utils.h"

DLLEXPORT double MADX9_MaterialCreate()
{
	_GMEXBEG();

	D3DMATERIAL9* mat = new D3DMATERIAL9;

	memset(mat, 0, sizeof(*mat));

	return putInto(mat, mamain->Material);

	_GMEXEND(-1, mamain->err, mamain->ignoreInv)
}

DLLEXPORT double MADX9_MaterialDestroy(double index)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	delete mamain->Material[(uint) index];
	mamain->Material[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_MaterialSetDiffuse(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->Material[(uint) index]->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_MaterialSetAmbient(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->Material[(uint) index]->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecular(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->Material[(uint) index]->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_MaterialSetSpecularPower(double index, double p)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->Material[(uint) index]->Power = (float) p;

	return 1;
}

DLLEXPORT double MADX9_MaterialSetEmissive(double index, double r, double g, double b, double a)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->Material[(uint) index]->Emissive = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return 1;
}

DLLEXPORT double MADX9_MaterialSet(double index)
{
	if ((uint) index >= mamain->Material.size())
		return 0;

	if (mamain->Material[(uint) index] == 0)
		return 0;

	mamain->d3ddev->SetMaterial(mamain->Material[(uint) index]);

	return 1;
}
