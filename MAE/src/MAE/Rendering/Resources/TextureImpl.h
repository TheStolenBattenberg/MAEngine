#pragma once

#include <MAE/MainImpl.h>
#include <MAE/Rendering/Resources/Texture.h>

class TextureImpl: public Texture {
public:
	TextureImpl(MainImpl* main): main(main) { };
	~TextureImpl();

	void release();

	void loadFromFile(std::string file, MipMaps mipmaps);
	void loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps);

	inline LPDIRECT3DTEXTURE9 getTexture() {
		return tex;
	}

private:
	MainImpl* main;
	LPDIRECT3DTEXTURE9 tex = 0;
};
