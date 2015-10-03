#include "dllbackend.h"

int MADLLBackend::HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, IDirect3DVertexShader9 ** VSOut, IDirect3DPixelShader9 ** PSOut)
{
	LPD3DXBUFFER VSCode;
	LPD3DXCONSTANTTABLE ConstantTable;
	HRESULT result;

	//Attempt to compile Vertex shader
	result = D3DXCompileShader(VertexShaderString, strlen(VertexShaderString), NULL, NULL, "main", "vs_3_0", D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, &VSCode, NULL, &ConstantTable);
	if(FAILED(result))
	{ VSCode->Release(); return 0; }

	//Attempt to create vertex shader
	result = d3ddev->CreateVertexShader((DWORD *) VSCode->GetBufferPointer(), VSOut);
	if(FAILED(result))
	{ VSCode->Release(); return 0; }

	return 1;
}
