#pragma once

#include <MAE/MainImpl.h>
#include <MAE/Rendering/Resources/Texture.h>

class TextureImpl: public Texture
{
public:
	TextureImpl(MainImpl* main): main(main) { };
	~TextureImpl();

	void release();

	ErrorCode create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool);
	ErrorCode createFromPointer(LPDIRECT3DTEXTURE9 ptr);
	ErrorCode generateMipMaps();
	ErrorCode getSurface(uint level, class Surface* surf);
	ErrorCode getSurfaceCount(uint& count);
	ErrorCode loadFromFile(std::string file, MipMaps mipmaps);
	ErrorCode loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps);
	ErrorCode setMipMapFilter(D3DTEXTUREFILTERTYPE filter);
	ErrorCode update(Texture* src);
	ErrorCode getTexture(LPDIRECT3DTEXTURE9& tex);

private:
	MainImpl* main;
	LPDIRECT3DTEXTURE9 tex = 0;

	enum
	{
		FlagMipMaps = 0x01
	};

	uint flags;
};
