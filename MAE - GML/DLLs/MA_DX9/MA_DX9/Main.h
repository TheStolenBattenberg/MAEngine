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

class MADX9Main
{
public:
	MADX9Main(LPDIRECT3DDEVICE9 d3ddev);
	~MADX9Main();

	const char* returnStr(std::string& str);
	
	Error err;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	std::vector<class Shader*>       Shader;
	std::vector<D3DLIGHT9*>          Light;
	std::vector<D3DMATERIAL9*>       Material;
	std::vector<class Surface*>      Surfaces;
	std::vector<class Texture*>      Textures;
	std::vector<class Buffer*>       Buffers;
	std::vector<class VertexDecl*>   VertexDeclarations;
	std::vector<class VertexBuffer*> VertexBuffers;

	std::vector<class MD2Model*> MD2Models;
	std::vector<class XModel*>   XModels;
	std::vector<class MPMModel*> MPMModels;

	std::vector<class ParticleSystem*> ParticleSys;

	class Hook* hook;

	DWORD stFVF;

	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationMPM = 0;
	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationParticle = 0;

	/**
	 * This stack can be used to transfer matrices to the DLL using MADX9_MatStackFloat and MADX9_MatStackClear
	 */

	std::vector<float> matStack;

	bool ignoreInv = 0;

private:
	std::string retStr;
};

extern MADX9Main* mamain;
