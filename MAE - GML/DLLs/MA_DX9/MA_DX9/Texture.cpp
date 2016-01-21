#include "Texture.h"
#include "Utils.h"
#include "Surface.h"

#include "MA_Main.h"

Texture::~Texture()
{
	if (tex != 0)
		tex->Release();
}

ErrorCode Texture::create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = mamain->d3ddev->CreateTexture(width, height, levels, usage, format, pool, &tex, 0);

	if (FAILED(res))
		return mamain->setError(ErrorCreateTexture);

	if (usage & D3DUSAGE_AUTOGENMIPMAP)
		flags |= FlagMipMaps;

	return ErrorOk;
}

ErrorCode Texture::generateMipMaps()
{
	if ((flags & FlagMipMaps) == 0)
		return mamain->setError(ErrorInv);

	tex->GenerateMipSubLevels();

	return ErrorOk;
}

ErrorCode Texture::getSurface(uint level, Surface* surf)
{
	if (level >= tex->GetLevelCount())
		return mamain->setError(ErrorInv);

	LPDIRECT3DSURFACE9 s;

	HRESULT res = tex->GetSurfaceLevel(level, &s);

	if (FAILED(res))
		return mamain->setError(ErrorD3D9);

	ErrorCode ret = surf->createFromPointer(s);

	s->Release();

	return ret;
}

ErrorCode Texture::getSurfaceCount(uint& count)
{
	if (tex == 0)
		return mamain->setError(ErrorInv);

	count = tex->GetLevelCount();
	return ErrorOk;
}

ErrorCode Texture::loadFromFile(std::string file, MipMaps mipmaps)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = D3DXCreateTextureFromFileEx(mamain->d3ddev, file.c_str(), 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

	if (FAILED(res))
		return mamain->setError(ErrorCreateTexture);

	return ErrorOk;
}

ErrorCode Texture::loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = D3DXCreateTextureFromFileInMemoryEx(mamain->d3ddev, data, length, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

	if (FAILED(res))
		return mamain->setError(ErrorCreateTexture);

	return ErrorOk;
}

ErrorCode Texture::setMipMapFilter(D3DTEXTUREFILTERTYPE filter)
{
	if ((flags & FlagMipMaps) == 0)
		return mamain->setError(ErrorInv);

	HRESULT res = tex->SetAutoGenFilterType(filter);

	if (FAILED(res))
		return mamain->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode Texture::update(Texture& src)
{
	HRESULT res = mamain->d3ddev->UpdateTexture(src.tex, tex);

	if (FAILED(res))
		return mamain->setError(ErrorD3D9);

	return ErrorOk;
}
