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

	ErrorCode checkFormat(D3DFORMAT adapdterFmt, uint usage, D3DRESOURCETYPE type, D3DFORMAT fmt, bool& exists);
	ErrorCode createScene(class Scene*& scene);
	ErrorCode createShader(class Shader*& shd);
	ErrorCode createTexture(class Texture*& tex);
	ErrorCode getError();
	ErrorCode onError(void(*func)(ErrorCode));
	ErrorCode resetShader();
	ErrorCode resetTexture(uint stage);
	ErrorCode setError(ErrorCode code);
	ErrorCode setShader(class Shader* shd);
	ErrorCode setTexture(uint stage, class Texture* tex);
	ErrorCode unregisterErrorFunction(void(*func)(ErrorCode));

	void removeScene(const class Scene* scene);
	void removeShader(const class Shader* shd);
	void removeTexture(const class Texture* tex);

private:
	ErrorCode errCode = ErrorOk;

	UnorderedVector<class SceneImpl*>   scenes;
	UnorderedVector<class TextureImpl*> textures;
	UnorderedVector<class ShaderImpl*>  shaders;

	std::list<void(*)(ErrorCode)> functions;
};
