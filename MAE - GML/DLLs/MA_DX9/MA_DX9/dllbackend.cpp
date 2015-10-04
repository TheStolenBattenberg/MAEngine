#include "dllbackend.h"

int MADLLBackend::HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, IDirect3DVertexShader9 ** VSOut, IDirect3DPixelShader9 ** PSOut)
{
	LPD3DXBUFFER VSCode, PSCode;
	LPD3DXCONSTANTTABLE ConstantTable;
	HRESULT result;
	__asm {int 03h}
	//Attempt to compile Vertex shader
	result = D3DXCompileShader(VertexShaderString, strlen(VertexShaderString), NULL, NULL, "main", "vs_3_0", D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, &VSCode, NULL, &ConstantTable);
	if(FAILED(result))
	{
		return 0;
	}
	
	//Attempt to create vertex shader
	result = d3ddev->CreateVertexShader((DWORD *) VSCode->GetBufferPointer(), VSOut);
	if(FAILED(result))
	{
		VSCode->Release();
		return 0;
	}
	
	//Atempt to compile Pixel Shader
	result = D3DXCompileShader(PixelShaderString, strlen(PixelShaderString), NULL, NULL, "main", "vs_3_0", D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, &PSCode, NULL, &ConstantTable);
	if(FAILED(result))
	{
		VSCode->Release();
		return 0;
	}
	
	//Atempt to create Pixel Shader
	result = d3ddev->CreatePixelShader((DWORD *) PSCode->GetBufferPointer(), PSOut);
	if(FAILED(result))
	{
		VSCode->Release();
		PSCode->Release();
		return 0;
	}
	
	return 1;
}
