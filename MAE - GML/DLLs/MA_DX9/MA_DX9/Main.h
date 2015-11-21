#pragma once

#define DLLEXPORT extern "C" __declspec (dllexport)

/**
 * Includes
 */

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <D3Dcompiler.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

#include "Hook.h"
#include "Error.h"
#include "Resources.h"

#include "Object.h"
#include "ModelMD2.h"

class MADX9Main
{
public:
	MADX9Main(LPDIRECT3DDEVICE9 d3ddev);
	~MADX9Main();

	const char* returnStr(std::string& str);
	
	Error err;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	std::vector<Shader*>       Shader;
	std::vector<D3DLIGHT9*>    Light;
	std::vector<D3DMATERIAL9*> Material;
	std::vector<MD2Model*>     MD2Models;
	std::vector<Surface*>      Surfaces;
	std::vector<Texture*>      Textures;

	Hook* hook;

	DWORD stFVF;

	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationMD2 = 0;
	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationMSM = 0;

	/**
	 * This stack can be used to transfer matrices to the DLL using MADX9_MatStackFloat and MADX9_MatStackClear
	 */

	std::vector<float> matStack;

private:
	std::string retStr;
};

extern MADX9Main* mamain;
