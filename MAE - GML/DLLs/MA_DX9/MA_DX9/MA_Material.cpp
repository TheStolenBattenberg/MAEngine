#include "Main.h"
#include "Types.h"
#include "Utils.h"

#include "MA_Main.h"

DLLEXPORT double MADX9_MaterialCreate()
{
	return putInto((D3DMATERIAL9*) memset(new D3DMATERIAL9, 0, sizeof(D3DMATERIAL9)), mamain->Material);
}

DLLEXPORT double MADX9_MaterialDestroy(double index)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	delete mamain->Material[(uint) index];
	mamain->Material[(uint) index] = 0;

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetDiffuse(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->Material[(uint) index]->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetAmbient(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->Material[(uint) index]->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetSpecular(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->Material[(uint) index]->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetSpecularPower(double index, double p)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->Material[(uint) index]->Power = (float) p;

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetEmissive(double index, double r, double g, double b, double a)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->Material[(uint) index]->Emissive = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSet(double index)
{
	if (!isValidIndex((uint) index, mamain->Material))
		return ErrorInv;

	mamain->d3ddev->SetMaterial(mamain->Material[(uint) index]);

	return ErrorOk;
}
