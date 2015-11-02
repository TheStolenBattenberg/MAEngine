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

class Exception {
	public:
		Exception(char* error)
		{
			exception = error;
		}
		char* exception;
};

class MADLLBackend
{
	public:
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 d3ddev;
		std::vector<IDirect3DVertexShader9*> VShader;
		std::vector<IDirect3DPixelShader9*> PShader;
		std::vector<D3DLIGHT9> Light;
		std::vector<MD2Model*> MD2Models; //This has to be done like this for now. For some reason the access to the Object functions are denied otherwise.

		DWORD stFVF;
		IDirect3DVertexDeclaration9* VertexDeclarationMD2 = 0;

		//Functions
		int HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, IDirect3DVertexShader9 ** VSOut, IDirect3DPixelShader9 ** PSOut);
};