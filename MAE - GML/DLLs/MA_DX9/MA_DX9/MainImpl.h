#pragma once

#include "Main.h"

#include <list>
#include <map>

class MainImpl: public Main
{
public:
	MainImpl(LPDIRECT3DDEVICE9 d3ddev);
	~MainImpl();

	uint release();

	ErrorCode createShader(class Shader*& shd);
	ErrorCode createSurface(class Surface*& surf);
	ErrorCode createTexture(class Texture*& tex);
	ErrorCode getError();
	ErrorCode onError(void(*func)(ErrorCode));
	ErrorCode resetRenderTarget(uint ind);
	ErrorCode resetShader();
	ErrorCode resetTexture(uint stage);
	ErrorCode setError(ErrorCode code);
	ErrorCode setRenderTarget(uint ind, class Surface* surf);
	ErrorCode setShader(class Shader* shd);
	ErrorCode setTexture(uint stage, class Texture* tex);
	ErrorCode unregisterErrorFunction(void(*func)(ErrorCode));

	void removeShader(const class Shader* shd);
	void removeSurface(const class Surface* surf);
	void removeTexture(const class Texture* tex);

private:
	ErrorCode errCode = ErrorOk;

	std::list<class SurfaceImpl*> surfaces;
	std::list<class TextureImpl*> textures;
	std::list<class ShaderImpl*>  shaders;

	std::list<void(*)(ErrorCode)> functions;
};
