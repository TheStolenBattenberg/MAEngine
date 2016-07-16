#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <MAE/Rendering/ModelMPM.h>
#include <MAE/Rendering/ModelMD2.h>
#include <MAE/Rendering/ModelX.h>

/**
 * Id .MD2 mesh.
 */

DLLEXPORT double MADX9_MD2Load(const char* MD2ModelFile, double tex, double normals) {
	auto texPtr = doubleToPtr<Texture>(tex);
	auto MD2 = new MD2Model(renderer);

	MD2->load(MD2ModelFile, normals >= 0.5);
	MD2->setTexture(texPtr);

	mamain->MD2Models.add(MD2);
	return ptrToDouble(MD2);
}

DLLEXPORT double MADX9_MD2Render(double md2, double frame_1, double frame_2, double tween) {
	auto ptr = doubleToPtr<MD2Model>(md2);

	ptr->render((uint) frame_1, (uint) frame_2, (float) tween);

	return 1;
}

DLLEXPORT double MADX9_MD2GetFrames(double md2) {
	auto ptr = doubleToPtr<MD2Model>(md2);

	return ptr->getFrameCount();
}

DLLEXPORT double MADX9_MD2Destroy(double md2) {
	auto ptr = doubleToPtr<MD2Model>(md2);

	mamain->MD2Models.remove(ptr);
	delete ptr;

	return 1;
}

/**
 * Microsoft .X mesh.
 */

DLLEXPORT double MADX9_XLoad(const char* XModelFile, const char* TextureDirectory) {
	auto x = new XModel(renderer);

	if (!x->load(XModelFile, TextureDirectory)) {
		delete x;
		return -1;
	}

	mamain->XModels.add(x);
	return ptrToDouble(x);
}

DLLEXPORT double MADX9_XRender(double x) {
	auto ptr = doubleToPtr<XModel>(x);

	for (uint i = 0; i < ptr->getMaterialCount(); ++i) {
		mamain->d3ddev->SetMaterial(&ptr->getMaterial(i));
		mamain->d3ddev->SetTexture(0, ptr->getTexture(i));
		ptr->getMesh()->DrawSubset(i);
	}

	return 1;
}

DLLEXPORT double MADX9_XDestroy(double x) {
	auto ptr = doubleToPtr<XModel>(x);

	mamain->XModels.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MAE_MPMLoad(const char* file) {
	auto m = new MPMModel(renderer);

	m->load(file);

	mamain->MPMModels.add(m);
	return ptrToDouble(m);
}

DLLEXPORT double MAE_MPMDestroy(double m) {
	auto ptr = doubleToPtr<MPMModel>(m);

	mamain->MPMModels.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MAE_MPMRender(double m) {
	auto ptr = doubleToPtr<MPMModel>(m);

	ptr->render();

	return 1;
}
