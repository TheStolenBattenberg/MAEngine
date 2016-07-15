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

#include <MAE/Core/Releasable.h>
#include <MAE/Core/UnorderedVector.h>
#include <MAE/Core/Types.h>

class Main: public Releasable {
public:
	virtual void release() = 0;

	virtual class Renderer* createRendererDX9(LPDIRECT3DDEVICE9 device) = 0;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	UnorderedVector<class MD2Model*> MD2Models;
	UnorderedVector<class XModel*>   XModels;
	UnorderedVector<class MPMModel*> MPMModels;

	UnorderedVector<class ParticleSystem*> ParticleSys;

	DWORD stFVF;

	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationParticle = 0;
};

extern Main* mainObj; // TODO: Remove

Main* MainCreate(LPDIRECT3DDEVICE9 device);
