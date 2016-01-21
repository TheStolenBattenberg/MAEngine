#include "Main.h"
#include "Types.h"
#include "Utils.h"
#include "Texture.h"

#include "MA_Main.h"

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	ErrorCode ret = tex->loadFromFile(file, mipmaps);

	if (ret != ErrorOk)
	{
		delete tex;
		return ret;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double ptr)
{
	Texture* tex = new Texture();

	if ((tex->tex = (LPDIRECT3DTEXTURE9) DoubleToPtr(ptr)) == 0)
	{
		delete tex;
		return mamain->setError(ErrorInv);
	}

	tex->tex->AddRef();

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	delete mamain->Textures[(uint)ind];
	mamain->Textures[(uint)ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_TextureSet(double ind, double stage)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	HRESULT res = mamain->d3ddev->SetTexture((uint)stage, mamain->Textures[(uint)ind]->tex);

	if (FAILED(res))
		return mamain->setError(ErrorD3D9);

	return ErrorOk;
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(const void* data, double length, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	ErrorCode ret = tex->loadFromFileInMemory(data, (uint) length, mipmaps);

	if (ret != ErrorOk)
	{
		delete tex;
		return ret;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureCreate(double width, double height, double levels, double usage, double format, double pool)
{
	Texture* tex = new Texture();

	ErrorCode ret = tex->create((uint) width, (uint) height, (uint) levels, (uint) usage, (D3DFORMAT) (uint) format, (D3DPOOL) (uint) pool);

	if (ret != ErrorOk)
	{
		delete tex;
		return ret;
	}

	return putInto(tex, mamain->Textures);
}

DLLEXPORT double MADX9_TextureGenerateMipMaps(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	return mamain->Textures[(uint) ind]->generateMipMaps();
}

DLLEXPORT double MADX9_TextureGetPointer(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	mamain->Textures[(uint) ind]->tex->AddRef();
	return PtrToDouble(mamain->Textures[(uint) ind]->tex);
}

DLLEXPORT double MADX9_TextureGetSurfaceCount(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	uint count;

	ErrorCode ret = mamain->Textures[(uint) ind]->getSurfaceCount(count);

	if (ret != ErrorOk)
		return ret;

	return count;
}

DLLEXPORT double MADX9_TextureSetMipMapFilter(double ind, double filter)
{
	if (!isValidIndex((uint) ind, mamain->Textures))
		return mamain->setError(ErrorInv);

	return mamain->Textures[(uint) ind]->setMipMapFilter((D3DTEXTUREFILTERTYPE) (uint) filter);
}

DLLEXPORT double MADX9_TextureUpdate(double dest, double src)
{
	if (!isValidIndex((uint) dest, mamain->Textures) ||
	    !isValidIndex((uint) src, mamain->Textures))
		return mamain->setError(ErrorInv);

	return mamain->Textures[(uint) dest]->update(*mamain->Textures[(uint) src]);
}
