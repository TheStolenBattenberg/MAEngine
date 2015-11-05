#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <D3Dcompiler.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

#include "Object.h"
#include "ObjectTerrain.h"
#include "ObjectModel.h"
#include "Hooks.h"
#include "Error.h"
#include "Resources.h"

class Exception {
	public:
		Exception(char* error)
		{
			exception = error;
		}
		char* exception;
};

class MADLLMain
{
public:
	MADLLMain();

	void init(LPDIRECT3DDEVICE9 d3ddev);
	void free();
	const char* returnStr(std::string str);
	bool isInitialized();

	Error err;

	LPDIRECT3D9       d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	std::vector<Shader*>   Shader;
	std::vector<D3DLIGHT9> Light;
	std::vector<MD2Model*> MD2Models;
	std::vector<D3DHooks*> Hooks;
	std::vector<Texture*>  Textures;

	DWORD stFVF;
	LPDIRECT3DVERTEXDECLARATION9 VertexDeclarationMD2 = 0;

private:
	std::string retStr;

	enum {
		FlagInitialized = 0x01
	};

	uint flags;
};

extern MADLLMain mamain;
