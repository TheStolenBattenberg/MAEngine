#pragma once

#define DLLEXPORT extern "C" __declspec (dllexport)

/**
 * Includes
 */

#include <Windows.h>

#include <d3d9.h>
#include <D3Dcompiler.h>
#include <d3dx9.h>
#include <fstream>
#include <vector>

#include "Error.h"
#include "RefCounted.h"

class Main: public RefCounted
{
public:
	virtual uint release() = 0;

	virtual ErrorCode surfaceCreate(class Surface*& surf) = 0;
	virtual ErrorCode surfaceExists(const class Surface* surf, bool& exists) = 0;

	virtual ErrorCode textureCreate(class Texture*& tex) = 0;
	virtual ErrorCode textureExists(const class Texture* tex, bool& exists) = 0;

	virtual ErrorCode shaderCreate(class Shader*& shd) = 0;
	virtual ErrorCode shaderExists(const class Shader* shd, bool& exists) = 0;

	virtual ErrorCode setTexture(uint stage, class Texture* tex) = 0;
	virtual ErrorCode resetTexture(uint stage) = 0;

	virtual ErrorCode setShader(class Shader* shd) = 0;
	virtual ErrorCode resetShader() = 0;

	virtual ErrorCode setError(ErrorCode code) = 0;
	virtual ErrorCode getError() = 0;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	std::vector<D3DLIGHT9*>          Light;
	std::vector<D3DMATERIAL9*>       Material;
	std::vector<class Buffer*>       Buffers;
	std::vector<class VertexDecl*>   VertexDeclarations;
	std::vector<class VertexBuffer*> VertexBuffers;

	std::vector<class MD2Model*> MD2Models;
	std::vector<class XModel*>   XModels;
	std::vector<class MPMModel*> MPMModels;

	std::vector<class ParticleSystem*> ParticleSys;

	class Hook* hook;

	DWORD stFVF;

	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationParticle = 0;
};

Main* MainCreate(LPDIRECT3DDEVICE9 device);
