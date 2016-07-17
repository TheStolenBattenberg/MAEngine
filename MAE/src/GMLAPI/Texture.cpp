#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/Renderer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, double mipmaps) {
	TRYBEG();
	return ptrToDouble(renderer->createTextureFromFile(file, (Renderer::MipMaps) (uint) mipmaps));
	TRYEND(0);
}

DLLEXPORT double MADX9_TextureDestroy(double tex) {
	TRYBEG();
	delete doubleToPtr<Texture>(tex);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_TextureSet(double stage, double tex) {
	TRYBEG();
	assert(("Stage cannot be less than 0", stage < 0));
	renderer->setTexture((uint) stage, doubleToPtr<Texture>(tex));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(const void* data, double length, double mipmaps) {
	TRYBEG();
	return ptrToDouble(renderer->createTextureFromFileInMemory(data, (uint) length, (Renderer::MipMaps) (uint) mipmaps));
	TRYEND(0);
}
