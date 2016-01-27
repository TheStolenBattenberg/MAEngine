#include "Texture.h"
#include "TextureImpl.h"
#include "Utils.h"
#include "Surface.h"

TextureImpl::~TextureImpl()
{
	if (tex != 0)
		tex->Release();
}

uint TextureImpl::release()
{
	if (--count == 0)
	{
		main->removeTexture(this);
		delete this;
	}

	return count;
}

ErrorCode TextureImpl::create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = main->d3ddev->CreateTexture(width, height, levels, usage, format, pool, &tex, 0);

	if (FAILED(res))
		return main->setError(ErrorCreateTexture);

	if (usage & D3DUSAGE_AUTOGENMIPMAP)
		flags |= FlagMipMaps;

	return ErrorOk;
}

ErrorCode TextureImpl::createFromPointer(LPDIRECT3DTEXTURE9 ptr)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	if (ptr == 0)
		return main->setError(ErrorInv);

	ptr->AddRef();
	tex = ptr;

	return ErrorOk;
}

ErrorCode TextureImpl::generateMipMaps()
{
	if ((flags & FlagMipMaps) == 0)
		return main->setError(ErrorInv);

	tex->GenerateMipSubLevels();

	return ErrorOk;
}

ErrorCode TextureImpl::getSurface(uint level, Surface* surf)
{
	if (level >= tex->GetLevelCount())
		return main->setError(ErrorInv);

	LPDIRECT3DSURFACE9 s;

	HRESULT res = tex->GetSurfaceLevel(level, &s);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	ErrorCode ret = surf->createFromPointer(s);

	s->Release();

	return ret;
}

ErrorCode TextureImpl::getSurfaceCount(uint& count)
{
	if (tex == 0)
		return main->setError(ErrorInv);

	count = tex->GetLevelCount();
	return ErrorOk;
}

ErrorCode TextureImpl::loadFromFile(std::string file, MipMaps mipmaps)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = D3DXCreateTextureFromFileEx(main->d3ddev, file.c_str(), 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

	if (FAILED(res))
		return main->setError(ErrorCreateTexture);

	return ErrorOk;
}

ErrorCode TextureImpl::loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps)
{
	if (tex != 0)
	{
		tex->Release();
		tex = 0;
	}

	flags = 0;

	HRESULT res = D3DXCreateTextureFromFileInMemoryEx(main->d3ddev, data, length, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

	if (FAILED(res))
		return main->setError(ErrorCreateTexture);

	return ErrorOk;
}

ErrorCode TextureImpl::setMipMapFilter(D3DTEXTUREFILTERTYPE filter)
{
	if ((flags & FlagMipMaps) == 0)
		return main->setError(ErrorInv);

	HRESULT res = tex->SetAutoGenFilterType(filter);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode TextureImpl::update(Texture* src)
{
	LPDIRECT3DTEXTURE9 t;

	ErrorCode ret = src->getTexture(t);

	if (ret != ErrorOk)
		return ret;

	HRESULT res = main->d3ddev->UpdateTexture(t, tex);

	t->Release();

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode TextureImpl::getTexture(LPDIRECT3DTEXTURE9& tex)
{
	if (this->tex == 0)
		return main->setError(ErrorInv);

	this->tex->AddRef();
	tex = this->tex;

	return ErrorOk;
}
