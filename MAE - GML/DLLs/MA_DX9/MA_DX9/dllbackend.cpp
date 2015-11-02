#include "dllbackend.h"

MADLLBackend marb;

int MADLLBackend::HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, LPDIRECT3DVERTEXSHADER9* VSOut, LPDIRECT3DPIXELSHADER9* PSOut)
{
	LPD3DXBUFFER Code;
	LPD3DXCONSTANTTABLE ConstantTable;
	HRESULT result;

	LPD3DXBUFFER buf;

	//Attempt to compile Vertex shader
	result = D3DXCompileShader(VertexShaderString, strlen(VertexShaderString), NULL, NULL, "main", "vs_3_0", D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, &Code, &buf, &ConstantTable);

	if (FAILED(result))
	{
		MessageBoxA(0, (char*)buf->GetBufferPointer(), "Failed to compile shader", MB_OK);
		buf->Release();
		return 0;
	}

	//Attempt to create vertex shader
	result = d3ddev->CreateVertexShader((DWORD *) Code->GetBufferPointer(), VSOut);
	
	Code->Release();

	if (FAILED(result))
		return 0;

	//Atempt to compile Pixel Shader
	result = D3DXCompileShader(PixelShaderString, strlen(PixelShaderString), NULL, NULL, "main", "vs_3_0", D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, &Code, &buf, &ConstantTable);
	
	if (FAILED(result))
	{
		MessageBoxA(0, (char*)buf->GetBufferPointer(), "Failed to compile shader", MB_OK);
		buf->Release();
		(*VSOut)->Release();
		return 0;
	}

	//Atempt to create Pixel Shader
	result = d3ddev->CreatePixelShader((DWORD *)Code->GetBufferPointer(), PSOut);

	Code->Release();
	
	if (FAILED(result))
	{
		(*VSOut)->Release();
		return 0;
	}
	
	return 1;
}
