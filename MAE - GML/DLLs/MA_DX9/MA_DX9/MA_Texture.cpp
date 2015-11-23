#include "Main.h"
#include "Types.h"
#include "Utils.h"

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	if (!tex->loadFromFile(file, mipmaps))
	{
		delete tex;
		return -1;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double ptr)
{
	Texture* tex = new Texture();

	tex->tex = *(LPDIRECT3DTEXTURE9*) &ptr;

	if (tex->tex == 0)
	{
		delete tex;
		return -1;
	}

	tex->tex->AddRef();

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return 0;

	delete mamain->Textures[(uint)ind];
	mamain->Textures[(uint)ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_TextureSet(double ind, double stage)
{
	if (ind < 0)
		return SUCCEEDED(mamain->d3ddev->SetTexture((uint)stage, 0));

	if (!isValidIndex((uint) ind, mamain->Textures))
		return 0;

	return SUCCEEDED(mamain->d3ddev->SetTexture((uint)stage, mamain->Textures[(uint)ind]->tex));
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(const void* data, double length, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	if (!tex->loadFromFileInMemory(data, (uint) length, mipmaps))
	{
		delete tex;
		return -1;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureCreate(double width, double height, double levels, double usage, double format, double pool)
{
	Texture* tex = new Texture();

	if (!tex->create((uint) width, (uint) height, (uint) levels, (uint) usage, (D3DFORMAT) (uint) format, (D3DPOOL) (uint) pool))
	{
		delete tex;
		return -1;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureGenerateMipMaps(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return 0;

	return mamain->Textures[(uint) ind]->generateMipMaps();
}

DLLEXPORT double MADX9_TextureGetPointer(double ind)
{
	void* ptr = 0;

	if (isValidIndex((uint) ind, mamain->Textures))
	{
		mamain->Textures[(uint) ind]->tex->AddRef();
		ptr = mamain->Textures[(uint) ind]->tex;
	}

	double ret = 0;

	*(void**) &ret = ptr;

	return ret;
}

DLLEXPORT double MADX9_TextureGetSurfaceCount(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return 0;

	return mamain->Textures[(uint) ind]->getSurfaceCount();
}

DLLEXPORT double MADX9_TextureSetMipMapFilter(double ind, double filter)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return 0;

	return mamain->Textures[(uint) ind]->setMipMapFilter((D3DTEXTUREFILTERTYPE) (uint) filter);
}

DLLEXPORT double MADX9_TextureUpdate(double dest, double src)
{
	if (!isValidIndex((uint) dest, mamain->Textures) ||
	    !isValidIndex((uint) src, mamain->Textures))
		return 0;

	return mamain->Textures[(uint) dest]->update(*mamain->Textures[(uint) src]);
}
