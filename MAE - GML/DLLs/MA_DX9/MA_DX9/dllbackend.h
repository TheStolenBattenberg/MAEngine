#include <Windows.h>
#include <WindowsX.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <D3Dcompiler.h>
#include <vector>

//#include "Object.h" Don't these inclde yet.
//#include "ObjectTerrain.h"

class MADLLBackend
{
	public:
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 d3ddev;
		std::vector<IDirect3DVertexShader9*> VShader;
		std::vector<IDirect3DPixelShader9*> PShader;
		std::vector<D3DLIGHT9> Light;

		//std::vector<Object*> Objects; We don't want this trying to compile yet.

		DWORD stFVF;

		//Functions
		int HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, IDirect3DVertexShader9 ** VSOut, IDirect3DPixelShader9 ** PSOut);
};
