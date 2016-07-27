#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <MAE/Rendering/TextureCollection.h>
#include <MAE/Rendering/Resources/Texture.h>

DLLEXPORT double MAE_TextureCollectionCreate() {
	TRYBEG();
	return ptrToDouble(new TextureCollection);
	TRYEND(0);
}

DLLEXPORT double MAE_TextureCollectionDestroy(double dir) {
	TRYBEG();
	delete doubleToPtr<TextureCollection>(dir);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_TextureCollectionAdd(double dir, const char* name, double tex) {
	TRYBEG();
	doubleToPtr<TextureCollection>(dir)->add(name, doubleToPtr<Texture>(tex));
	return 1;
	TRYEND(0);
}
