#pragma once

#include <MAE/MainImpl.h>
#include <MAE/Rendering/Resources/Texture.h>

class TextureImpl: public Texture {
public:
	TextureImpl(LPDIRECT3DTEXTURE9 tex): tex(tex) { }
	~TextureImpl();

	inline LPDIRECT3DTEXTURE9 getTexture() {
		return tex;
	}

private:
	LPDIRECT3DTEXTURE9 tex;
};
