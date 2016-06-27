#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_MaterialCreate()
{
	auto mat = (D3DMATERIAL9*) memset(new D3DMATERIAL9, 0, sizeof(D3DMATERIAL9));

	mamain->Material.add(mat);

	return ptrToDouble(mat);
}

DLLEXPORT double MADX9_MaterialDestroy(double material)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	mamain->Material.remove(ptr);
	delete ptr;

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetDiffuse(double material, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	ptr->Diffuse = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetAmbient(double material, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	ptr->Ambient = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetSpecular(double material, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	ptr->Specular = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetSpecularPower(double material, double p)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	ptr->Power = (float) p;

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSetEmissive(double material, double r, double g, double b, double a)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	ptr->Emissive = D3DXCOLOR((float) r, (float) g, (float) b, (float) a);

	return ErrorOk;
}

DLLEXPORT double MADX9_MaterialSet(double material)
{
	auto ptr = doubleToPtr<D3DMATERIAL9>(material);

	mamain->d3ddev->SetMaterial(ptr);

	return ErrorOk;
}
