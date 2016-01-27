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

	virtual ErrorCode createShader(class Shader*& shd) = 0;
	virtual ErrorCode createSurface(class Surface*& surf) = 0;
	virtual ErrorCode createTexture(class Texture*& tex) = 0;
	virtual ErrorCode getError() = 0;
	virtual ErrorCode onError(void(*func)(ErrorCode)) = 0;
	virtual ErrorCode resetRenderTarget(uint ind) = 0;
	virtual ErrorCode resetShader() = 0;
	virtual ErrorCode resetTexture(uint stage) = 0;
	virtual ErrorCode setError(ErrorCode code) = 0;
	virtual ErrorCode setRenderTarget(uint ind, class Surface* surf) = 0;
	virtual ErrorCode setShader(class Shader* shd) = 0;
	virtual ErrorCode setTexture(uint stage, class Texture* tex) = 0;
	virtual ErrorCode unregisterErrorFunction(void(*func)(ErrorCode)) = 0;

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
