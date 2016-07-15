#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/Renderer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, double mipmaps) {
	return ptrToDouble(renderer->createTextureFromFile(file, (Renderer::MipMaps) (uint) mipmaps));
}

DLLEXPORT double MADX9_TextureDestroy(double tex) {
	delete doubleToPtr<Texture>(tex);
	return 1;
}

DLLEXPORT double MADX9_TextureSet(double stage, double tex) {
	assert(("Stage cannot be less than 0", stage < 0));
	renderer->setTexture((uint) stage, doubleToPtr<Texture>(tex));
	return 1;
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(const void* data, double length, double mipmaps) {
	return ptrToDouble(renderer->createTextureFromFileInMemory(data, (uint) length, (Renderer::MipMaps) (uint) mipmaps));
}
