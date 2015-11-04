#include "dllbackend.h"

MADLLBackend marb;

MADLLBackend::MADLLBackend()
{
	err.flags = ErrorShowMessage | ErrorShowDebugMessage;
}

bool MADLLBackend::HLSL9Compile(LPCSTR VertexShaderString, LPCSTR PixelShaderString, LPDIRECT3DVERTEXSHADER9* VSOut, LPDIRECT3DPIXELSHADER9* PSOut)
{
	LPD3DXBUFFER Code;
	LPD3DXCONSTANTTABLE ConstantTable;
	HRESULT result;

	LPD3DXBUFFER buf;

	//Attempt to compile Vertex shader
	result = D3DXCompileShader(VertexShaderString, strlen(VertexShaderString), NULL, NULL, "main", D3DXGetVertexShaderProfile(marb.d3ddev), 0, &Code, &buf, &ConstantTable);

	if (FAILED(result))
	{
		err.onError((char*) buf->GetBufferPointer());
		buf->Release();
		return 0;
	}

	//Attempt to create vertex shader
	result = d3ddev->CreateVertexShader((DWORD *) Code->GetBufferPointer(), VSOut);
	
	Code->Release();

	if (FAILED(result))
	{
		err.onErrorDX9("Failed to create vertex shader", result);
		return 0;
	}

	//Atempt to compile Pixel Shader
	result = D3DXCompileShader(PixelShaderString, strlen(PixelShaderString), NULL, NULL, "main", D3DXGetPixelShaderProfile(marb.d3ddev), 0, &Code, &buf, &ConstantTable);
	
	if (FAILED(result))
	{
		err.onError((char*) buf->GetBufferPointer());
		buf->Release();
		(*VSOut)->Release();
		return 0;
	}

	//Atempt to create Pixel Shader
	result = d3ddev->CreatePixelShader((DWORD *)Code->GetBufferPointer(), PSOut);

	Code->Release();
	
	if (FAILED(result))
	{
		err.onErrorDX9("Failed to create pixel shader", result);
		(*VSOut)->Release();
		return 0;
	}
	
	return 1;
}
