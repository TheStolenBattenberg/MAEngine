#include "Main.h"
#include "Resources.h"

Shader::~Shader() {
	if (VShader != 0)
		VShader->Release();

	if (PShader != 0)
		PShader->Release();

	if (VConstants != 0)
		VConstants->Release();

	if (PConstants != 0)
		PConstants->Release();
}

bool Shader::compile(std::string vert, std::string pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result = D3DXCompileShader(vert.c_str(), vert.length(), NULL, NULL, "main", D3DXGetVertexShaderProfile(mamain.d3ddev), 0, &code, &err, &VConstants);

	if (FAILED(result)) {
		mamain.err.onError((char*) err->GetBufferPointer());
		
		err->Release();

		return 0;
	}

	result = mamain.d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &VShader);

	code->Release();

	if (FAILED(result)) {
		mamain.err.onErrorDX9("Failed to create vertex shader", result);

		VConstants->Release();
		VConstants = 0;

		return 0;
	}

	result = D3DXCompileShader(pixel.c_str(), pixel.length(), NULL, NULL, "main", D3DXGetPixelShaderProfile(mamain.d3ddev), 0, &code, &err, &PConstants);

	if (FAILED(result)) {
		mamain.err.onError((char*) err->GetBufferPointer());

		err->Release();
		VShader->Release();
		VConstants->Release();

		VShader    = 0;
		VConstants = 0;

		return 0;
	}

	result = mamain.d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &PShader);

	code->Release();

	if (FAILED(result)) {
		mamain.err.onErrorDX9("Failed to create pixel shader", result);

		VShader->Release();
		VConstants->Release();
		PConstants->Release();

		VShader    = 0;
		VConstants = 0;
		PConstants = 0;

		return 0;
	}

	return 1;
}

Texture::~Texture() {
	if (texSys != 0)
		texSys->Release();

	if (texGPU != 0)
		texGPU->Release();
}

bool Texture::loadFromFile(std::string file, bool mipmaps) {
	HRESULT res = D3DXCreateTextureFromFileEx(mamain.d3ddev, file.c_str(), 0, 0, mipmaps ? 0 : 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texSys);

	if (FAILED(res)) {
		mamain.err.onErrorDX9("Couldn't load texture", res);
		return 0;
	}

	return 1;
}

void Texture::upload() {
	// TODO: Upload texture to gpu
}

void Texture::freeGPU() {
	if (texGPU != 0)
		texGPU->Release();
}