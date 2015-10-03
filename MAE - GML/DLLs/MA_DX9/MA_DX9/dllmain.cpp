#define DLLEXPORT extern "C" __declspec (dllexport)

#include "dllbackend.h"

MADLLBackend MARenderBackend;

DLLEXPORT double MADX9_Init(long pointer)
{
	MARenderBackend.d3ddev = (LPDIRECT3DDEVICE9) pointer;
	return 1;
}

DLLEXPORT double MADX9_ShaderCreateHLSL9(char* VSCode, char* PSCode)
{
	IDirect3DVertexShader9 *VShd;
	IDirect3DPixelShader9 *PShd;

	//Compile the Shader
	if(MARenderBackend.HLSL9Compile(VSCode, PSCode, &VShd, &PShd) == 0) 
	{ return 0; }

	//Add shaders to container and return shader index;
	MARenderBackend.VShader.push_back(VShd);
	MARenderBackend.PShader.push_back(PShd);
	return MARenderBackend.PShader.size()-1;
}

DLLEXPORT double MADX9_ShaderSetHLSL9(double index)
{
	HRESULT result;

	//Store the current Fixed Vertex Format.
	MARenderBackend.d3ddev->GetFVF(&MARenderBackend.stFVF);

	int ShaderIndex = (int) index;

	//Set the Vertex Shader
	result = MARenderBackend.d3ddev->SetVertexShader(MARenderBackend.VShader[ShaderIndex]);
	if(FAILED(result)) { return 0; }

	//Set the Pixel Shader
	result = MARenderBackend.d3ddev->SetPixelShader(MARenderBackend.PShader[ShaderIndex]);
	if(FAILED(result)) { return 0; }

	return 1;
}

DLLEXPORT double MADX9_ShaderResetHLSL9()
{
	HRESULT result;

	//Reset the Vertex Shader.
	result = MARenderBackend.d3ddev->SetVertexShader(NULL);
	if(FAILED(result)) { return 0; }

	//Reset the Pixel Shader.
	result = MARenderBackend.d3ddev->SetPixelShader(NULL);
	if(FAILED(result)) { return 0; }

	MARenderBackend.d3ddev->SetFVF(MARenderBackend.stFVF);
	return 1;
}

DLLEXPORT double MADX9_ShaderDestroyHLSL9(double index)
{
	int ShaderIndex = (int) index;

	//Delete Vertex Shader
	MARenderBackend.VShader[ShaderIndex]->Release();
	MARenderBackend.VShader.erase(MARenderBackend.VShader.begin() + ShaderIndex);

	//Delete Pixel Shader
	MARenderBackend.PShader[ShaderIndex]->Release();
	MARenderBackend.PShader.erase(MARenderBackend.PShader.begin() + ShaderIndex);

	return 1;
}
