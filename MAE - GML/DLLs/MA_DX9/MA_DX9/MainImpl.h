#pragma once

#include "Main.h"

#include <list>

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
	ErrorCode resetShader();
	ErrorCode resetTexture(uint stage);
	ErrorCode setError(ErrorCode code);
	ErrorCode setShader(class Shader* shd);
	ErrorCode setTexture(uint stage, class Texture* tex);

	void removeShader(const class Shader* shd);
	void removeSurface(const class Surface* surf);
	void removeTexture(const class Texture* tex);

private:
	ErrorCode errCode;
	std::list<class SurfaceImpl*> surfaces;
	std::list<class TextureImpl*> textures;
	std::list<class ShaderImpl*>  shaders;
};
