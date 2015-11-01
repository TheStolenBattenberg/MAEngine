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

		std::vector<Object*> Objects;

		DWORD stFVF;

		//Functions
		int HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, IDirect3DVertexShader9 ** VSOut, IDirect3DPixelShader9 ** PSOut);
};