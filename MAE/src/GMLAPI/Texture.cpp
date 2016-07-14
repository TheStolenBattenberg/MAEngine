#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_TextureCreate() {
	return ptrToDouble(mamain->createTexture());
}

DLLEXPORT double MADX9_TextureCreateFromFile(double tex, const char* file, Texture::MipMaps mipmaps) {
	doubleToPtr<Texture>(tex)->loadFromFile(file, mipmaps);
	return 1;
}

DLLEXPORT double MADX9_TextureDestroy(double tex) {
	delete doubleToPtr<Texture>(tex);
	return 1;
}

DLLEXPORT double MADX9_TextureSet(double stage, double tex) {
	assert(("Stage cannot be less than 0", stage < 0));
	mamain->setTexture((uint) stage, doubleToPtr<Texture>(tex));
	return 1;
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(double tex, const void* data, double length, Texture::MipMaps mipmaps) {
	doubleToPtr<Texture>(tex)->loadFromFileInMemory(data, (uint) length, mipmaps);
	return 1;
}
