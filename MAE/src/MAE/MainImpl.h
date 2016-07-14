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

	class Scene* createScene();
	class Shader* createShader();
	class Texture* createTexture();
	void setShader(class Shader* shd);
	void setTexture(uint stage, class Texture* tex);

	void removeScene(const class Scene* scene);
	void removeShader(const class Shader* shd);
	void removeTexture(const class Texture* tex);

private:
	UnorderedVector<class SceneImpl*>   scenes;
	UnorderedVector<class TextureImpl*> textures;
	UnorderedVector<class ShaderImpl*>  shaders;
};
