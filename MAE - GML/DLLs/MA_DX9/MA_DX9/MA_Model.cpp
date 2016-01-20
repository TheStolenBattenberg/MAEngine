#include "Main.h"
#include "Types.h"
#include "Utils.h"
#include "Texture.h"

#include "MA_Main.h"

#include "ModelMPM.h"
#include "ModelMD2.h"
#include "ModelX.h"

/**
 * Id .MD2 mesh.
 */

DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, double texInd, double normals)
{
	if (!isValidIndex((uint) texInd, mamain->Textures))
		return -1;

	MD2Model* MD2 = new MD2Model();

	if (!MD2->load(MD2ModelFile, normals >= 0.5))
	{
		delete MD2;
		return -1;
	}

	MD2->setTexture(mamain->Textures[(uint)texInd]->tex);

	return putInto(MD2, mamain->MD2Models);
}

DLLEXPORT double MADX9_MD2Render(double index, double frame_1, double frame_2, double tween)
{
	if (!isValidIndex((uint) index, mamain->MD2Models))
		return 0;

	MD2Model* MD2 = mamain->MD2Models[(uint) index];

	MD2->render((uint) frame_1, (uint) frame_2, (float) tween);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double index)
{
	if (!isValidIndex((uint) index, mamain->MD2Models))
		return -1;

	return mamain->MD2Models[(uint)index]->getFrameCount();
}

DLLEXPORT double MADX9_MD2Destroy(double index)
{
	if (!isValidIndex((uint) index, mamain->MD2Models))
		return 0;

	delete mamain->MD2Models[(uint) index];
	mamain->MD2Models[(uint) index] = 0;

	return 1;
}

/**
 * Microsoft .X mesh.
 */

DLLEXPORT double MADX9_XLoad(const char* XModelFile, const char* TextureDirectory)
{
	XModel* x = new XModel();
	if (!x->load(XModelFile, TextureDirectory)) {
		delete x;
		return -1;
	}

	for (size_t i = 0; i < mamain->XModels.size(); ++i)
	{
		if (mamain->XModels[i] == 0)
		{
			mamain->XModels[i] = x;
			return i;
		}
	}

	mamain->XModels.push_back(x);
	return mamain->XModels.size() - 1;
}

DLLEXPORT double MADX9_XRender(double index)
{
	if ((uint)index > mamain->XModels.size()) {
		return 0;
	}

	XModel* x = mamain->XModels[(uint)index];

	for (uint i = 0; i < x->getMaterialCount(); ++i) {
		mamain->d3ddev->SetMaterial(&x->getMaterial(i));
		mamain->d3ddev->SetTexture(0, x->getTexture(i));
		x->getMesh()->DrawSubset(i);
	}

	return 1;
}

DLLEXPORT double MADX9_XDestroy(double index) 
{
	if ((uint)index > mamain->XModels.size()) {
		return 0;
	}

	delete mamain->XModels[(uint)index];
	mamain->XModels[(uint)index] = 0;
	return 1;
}

DLLEXPORT double MAE_MPMLoad(const char* file)
{
	MPMModel* m = new MPMModel();

	ErrorCode res = m->load(file);

	if (res != ErrorOk)
		return res;

	return putInto(m, mamain->MPMModels);
}

DLLEXPORT double MAE_MPMDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->MPMModels))
		return 0;

	delete mamain->MPMModels[(uint) ind];
	mamain->MPMModels[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MAE_MPMRender(double ind)
{
	if (!isValidIndex((uint) ind, mamain->MPMModels))
		return 0;

	mamain->MPMModels[(uint) ind]->render();

	return 1;
}
