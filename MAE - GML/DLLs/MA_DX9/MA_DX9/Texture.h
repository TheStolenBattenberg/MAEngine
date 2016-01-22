#pragma once

#include "Error.h"
#include "RefCounted.h"

#include <d3d9.h>
#include <string>

class Texture: public RefCounted
{
public:
	enum MipMaps
	{
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	virtual ErrorCode create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool) = 0;
	virtual ErrorCode createFromPointer(LPDIRECT3DTEXTURE9 ptr) = 0;
	virtual ErrorCode generateMipMaps() = 0;
	virtual ErrorCode getSurface(uint level, class Surface* surf) = 0;
	virtual ErrorCode getSurfaceCount(uint& count) = 0;
	virtual ErrorCode loadFromFile(std::string file, MipMaps mipmaps) = 0;
	virtual ErrorCode loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps) = 0;
	virtual ErrorCode setMipMapFilter(D3DTEXTUREFILTERTYPE filter) = 0;
	virtual ErrorCode update(Texture* src) = 0;
	virtual ErrorCode getTexture(LPDIRECT3DTEXTURE9& tex) = 0;
};
