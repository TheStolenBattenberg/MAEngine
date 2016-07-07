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

#include <MAE/Core/Error.h>
#include <MAE/Core/Releasable.h>
#include <MAE/Core/UnorderedVector.h>

class Main: public Releasable
{
public:
	virtual void release() = 0;

	virtual class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device) = 0;

	virtual ErrorCode checkFormat(D3DFORMAT adapdterFmt, uint usage, D3DRESOURCETYPE type, D3DFORMAT fmt, bool& exists) = 0;
	virtual ErrorCode createScene(class Scene*& scene) = 0;
	virtual ErrorCode createShader(class Shader*& shd) = 0;
	virtual ErrorCode createTexture(class Texture*& tex) = 0;
	virtual ErrorCode getError() = 0;
	virtual ErrorCode onError(void(*func)(ErrorCode)) = 0;
	virtual ErrorCode resetShader() = 0;
	virtual ErrorCode resetTexture(uint stage) = 0;
	virtual ErrorCode setError(ErrorCode code) = 0;
	virtual ErrorCode setShader(class Shader* shd) = 0;
	virtual ErrorCode setTexture(uint stage, class Texture* tex) = 0;
	virtual ErrorCode unregisterErrorFunction(void(*func)(ErrorCode)) = 0;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	UnorderedVector<class VertexDecl*>   VertexDeclarations;
	
	UnorderedVector<class MD2Model*> MD2Models;
	UnorderedVector<class XModel*>   XModels;
	UnorderedVector<class MPMModel*> MPMModels;

	UnorderedVector<class ParticleSystem*> ParticleSys;

	DWORD stFVF;

	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationParticle = 0;
};

extern Main* mainObj; // TODO: Remove

Main* MainCreate(LPDIRECT3DDEVICE9 device);
