#pragma once

#include <MAE/Main.h>

class MainImpl: public Main {
public:
	~MainImpl();

	class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device);

private:
	UnorderedVector<class SceneImpl*>   scenes;
	UnorderedVector<class TextureImpl*> textures;
	UnorderedVector<class ShaderImpl*>  shaders;
};
