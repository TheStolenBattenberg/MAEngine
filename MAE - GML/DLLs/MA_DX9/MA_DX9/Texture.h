#pragma once

#include "Main.h"

class Texture
{
public:
	enum MipMaps
	{
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	~Texture();

	ErrorCode create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool);
	ErrorCode generateMipMaps();
	ErrorCode getSurface(uint level, class Surface& surf);
	ErrorCode getSurfaceCount(uint& count);
	ErrorCode loadFromFile(std::string file, MipMaps mipmaps);
	ErrorCode loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps);
	ErrorCode setMipMapFilter(D3DTEXTUREFILTERTYPE filter);
	ErrorCode update(Texture& src);

	LPDIRECT3DTEXTURE9 tex = 0;

private:
	enum
	{
		FlagMipMaps = 0x01
	};

	uint flags;
};
