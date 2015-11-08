#include "Main.h"
#include "Resources.h"

ShaderConstants::~ShaderConstants() {
	if (constants != 0)
		constants->Release();
}

uint ShaderConstants::find(std::string c) {
	D3DXHANDLE h = constants->GetConstantByName(0, c.c_str());

	if (h == 0)
		return 0;

	for (uint i = 0; i < handles.size(); ++i)
		if (handles[i] == h)
			return i;

	handles.push_back(h);
	return handles.size() - 1;
}

uint ShaderConstants::getSampler(uint c) {
	if (c >= handles.size())
		return InvalidSampler;

	return constants->GetSamplerIndex(handles[c]);
}

bool ShaderConstants::setFloat(uint c, float f) {
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloat(mamain.d3ddev, handles[c], f));
}

bool ShaderConstants::setVec2(uint c, const vec2& v) {
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloatArray(mamain.d3ddev, handles[c], v, sizeof(v) / sizeof(*v)));
}

bool ShaderConstants::setVec3(uint c, const vec3& v)
{
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloatArray(mamain.d3ddev, handles[c], v, sizeof(v) / sizeof(*v)));
}

bool ShaderConstants::setVec4(uint c, const vec4& v)
{
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloatArray(mamain.d3ddev, handles[c], v, sizeof(v) / sizeof(*v)));
}

bool ShaderConstants::setMat3(uint c, const mat3& v)
{
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloatArray(mamain.d3ddev, handles[c], v, sizeof(v) / sizeof(*v)));
}

bool ShaderConstants::setMat4(uint c, const mat4& v)
{
	if (c >= handles.size())
		return 0;

	return SUCCEEDED(constants->SetFloatArray(mamain.d3ddev, handles[c], v, sizeof(v) / sizeof(*v)));
}

Shader::~Shader() {
	if (VShader != 0)
		VShader->Release();

	if (PShader != 0)
		PShader->Release();
}

bool Shader::compileasm(std::string vert, std::string pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	//Assemble Vertex Shader
	{
		HRESULT result = D3DXAssembleShader(vert.c_str(), vert.length(), NULL, NULL, 0, &code, &err);
		if (FAILED(result)) {
			mamain.err.onError((char*)err->GetBufferPointer());
			err->Release();

			return 0;
		}

		result = mamain.d3ddev->CreateVertexShader((DWORD*)code->GetBufferPointer(), &VShader);
		code->Release();

		if (FAILED(result)) {
			mamain.err.onErrorDX9("Failed to create vertex shader", result);

			return 0;
		}
	}


	//Assemble Pixel Shader
	{
		HRESULT result = D3DXAssembleShader(pixel.c_str(), pixel.length(), NULL, NULL, 0, &code, &err);
		if (FAILED(result)) {
			mamain.err.onError((char*)err->GetBufferPointer());
			err->Release();

			VShader->Release();
			VShader = 0;

			return 0;
		}

		result = mamain.d3ddev->CreatePixelShader((DWORD*)code->GetBufferPointer(), &PShader);
		code->Release();

		if (FAILED(result)) {
			mamain.err.onErrorDX9("Failed to create pixel shader", result);

			VShader->Release();
			VShader = 0;

			return 0;
		}
	}
	return 1;
}

bool Shader::compile(std::string vert, std::string pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result = D3DXCompileShader(vert.c_str(), vert.length(), NULL, NULL, "main", D3DXGetVertexShaderProfile(mamain.d3ddev), 0, &code, &err, &VConstants.constants);
	
	if (FAILED(result)) {
		mamain.err.onError((char*) err->GetBufferPointer());
		
		err->Release();

		return 0;
	}

	result = mamain.d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &VShader);

	code->Release();

	if (FAILED(result)) {
		mamain.err.onErrorDX9("Failed to create vertex shader", result);
		return 0;
	}

	result = D3DXCompileShader(pixel.c_str(), pixel.length(), NULL, NULL, "main", D3DXGetPixelShaderProfile(mamain.d3ddev), 0, &code, &err, &PConstants.constants);

	if (FAILED(result)) {
		mamain.err.onError((char*) err->GetBufferPointer());

		err->Release();
		
		VShader->Release();
		VShader = 0;

		return 0;
	}

	result = mamain.d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &PShader);

	code->Release();

	if (FAILED(result)) {
		mamain.err.onErrorDX9("Failed to create pixel shader", result);

		VShader->Release();
		VShader = 0;
		
		return 0;
	}

	return 1;
}

Texture::~Texture() {
	if (tex != 0)
		tex->Release();
}

bool Texture::loadFromFile(std::string file, MipMaps mipmaps) {
	HRESULT res = D3DXCreateTextureFromFileEx(mamain.d3ddev, file.c_str(), 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

	if (FAILED(res)) {
		mamain.err.onErrorDX9("Couldn't load texture", res);
		return 0;
	}

	return 1;
}
