#pragma once

#include <MAE/Main.h>


#include <list>
#include <map>

class MainImpl: public Main
{
public:
	MainImpl(LPDIRECT3DDEVICE9 d3ddev);
	~MainImpl();

	void release();

	class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device);

private:
	UnorderedVector<class SceneImpl*>   scenes;
	UnorderedVector<class TextureImpl*> textures;
	UnorderedVector<class ShaderImpl*>  shaders;
};
