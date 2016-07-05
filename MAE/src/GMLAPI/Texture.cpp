#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_TextureCreate()
{
	Texture* tex;
	
	ErrorCode ret = mamain->createTexture(tex);

	if (ret != ErrorOk)
		return ret;

	return ptrToDouble(tex);
}

DLLEXPORT double MADX9_TextureCreateFromFile(double tex, const char* file, Texture::MipMaps mipmaps)
{
	return doubleToPtr<Texture>(tex)->loadFromFile(file, mipmaps);
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double tex, double ptr)
{
	return doubleToPtr<Texture>(tex)->createFromPointer(doubleToPtr<IDirect3DTexture9>(ptr));
}

DLLEXPORT double MADX9_TextureDestroy(double tex)
{
	delete doubleToPtr<Texture>(tex);
	return 1;
}

DLLEXPORT double MADX9_TextureSet(double stage, double tex)
{
	assert(("Stage cannot be 0", stage < 0));

	return mamain->setTexture((uint) stage, doubleToPtr<Texture>(tex));
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(double tex, const void* data, double length, Texture::MipMaps mipmaps)
{
	return doubleToPtr<Texture>(tex)->loadFromFileInMemory(data, (uint) length, mipmaps);
}

DLLEXPORT double MADX9_TextureCreateEmpty(double tex, double width, double height, double levels, double usage, double format, double pool)
{
	return doubleToPtr<Texture>(tex)->create((uint) width, (uint) height, (uint) levels, (uint) usage, (D3DFORMAT) (uint) format, (D3DPOOL) (uint) pool);
}

DLLEXPORT double MADX9_TextureGenerateMipMaps(double tex)
{
	return doubleToPtr<Texture>(tex)->generateMipMaps();
}

DLLEXPORT double MADX9_TextureGetPointer(double tex)
{
	LPDIRECT3DTEXTURE9 t;

	return doubleToPtr<Texture>(tex)->getTexture(t) != ErrorOk ? ptrToDouble<void>(nullptr) : ptrToDouble(t);
}

DLLEXPORT double MADX9_TextureSetMipMapFilter(double tex, double filter)
{
	return doubleToPtr<Texture>(tex)->setMipMapFilter((D3DTEXTUREFILTERTYPE) (uint) filter);
}

DLLEXPORT double MADX9_TextureUpdate(double dest, double src)
{
	return doubleToPtr<Texture>(dest)->update(doubleToPtr<Texture>(src));
}
