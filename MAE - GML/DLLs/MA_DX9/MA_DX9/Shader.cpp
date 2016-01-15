#include "Shader.h"
#include "Utils.h"

Shader::ShaderConstants::~ShaderConstants()
{
	if (constants != 0)
		constants->Release();
}

ErrorCode Shader::ShaderConstants::find(const std::string& c, uint& ind)
{
	D3DXHANDLE h = constants->GetConstantByName(0, c.c_str());

	if (h == 0)
		return ErrorHandle(mamain->err, ErrorInv);

	for (uint i = 0; i < handles.size(); ++i)
	{
		if (handles[i] == h)
		{
			ind = i;
			return ErrorOk;
		}
	}

	handles.push_back(h);
	ind = handles.size() - 1;

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::getSampler(uint c, uint& ind) {
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	ind = constants->GetSamplerIndex(handles[c]);
	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setFloat(uint c, float f) {
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloat(mamain->d3ddev, handles[c], f);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloat");

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setVec2(uint c, const vec2& v) {
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloatArray(mamain->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloatArray");

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setVec3(uint c, const vec3& v)
{
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloatArray(mamain->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloatArray");

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setVec4(uint c, const vec4& v)
{
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloatArray(mamain->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloatArray");

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setMat3(uint c, const mat3& v)
{
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloatArray(mamain->d3ddev, handles[c], v.data, v.size * v.size);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloatArray");

	return ErrorOk;
}

ErrorCode Shader::ShaderConstants::setMat4(uint c, const mat4& v)
{
	if (c >= handles.size())
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res = constants->SetFloatArray(mamain->d3ddev, handles[c], v.data, v.size * v.size);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetFloatArray");

	return ErrorOk;
}

Shader::~Shader() {
	if (VShader != 0)
		VShader->Release();

	if (PShader != 0)
		PShader->Release();
}

ErrorCode Shader::compileASM(const std::string& vert, const std::string& pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	/**
	* Assemble Vertex Shader
	*/

	result = D3DXAssembleShader(vert.c_str(), vert.length(), NULL, NULL, 0, &code, &err);

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCompileVertexShader, result, (char*) err->GetBufferPointer());
		err->Release();

		return ErrorCompileVertexShader;
	}

	result = mamain->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &VShader);
	code->Release();

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCreateVertexShader, result);

	/**
	* Assemble Pixel Shader
	*/

	result = D3DXAssembleShader(pixel.c_str(), pixel.length(), NULL, NULL, 0, &code, &err);

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCompilePixelShader, result, (char*) err->GetBufferPointer());
		err->Release();

		VShader->Release();
		VShader = 0;

		return ErrorCompilePixelShader;
	}

	result = mamain->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &PShader);
	code->Release();

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCreatePixelShader, result);

		VShader->Release();
		VShader = 0;

		return ErrorCreatePixelShader;
	}

	return ErrorOk;
}

ErrorCode Shader::compile(const std::string& vert, const std::string& pixel)
{
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	result = D3DXCompileShader(vert.c_str(), vert.length(), NULL, NULL, "main", D3DXGetVertexShaderProfile(mamain->d3ddev), 0, &code, &err, &VConstants.constants);

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCompileVertexShader, result, (char*) err->GetBufferPointer());
		err->Release();

		return ErrorCompileVertexShader;
	}

	result = mamain->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &VShader);

	code->Release();

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCreateVertexShader, result);

	result = D3DXCompileShader(pixel.c_str(), pixel.length(), NULL, NULL, "main", D3DXGetPixelShaderProfile(mamain->d3ddev), 0, &code, &err, &PConstants.constants);

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCompilePixelShader, result, (char*) err->GetBufferPointer());
		err->Release();

		VShader->Release();
		VShader = 0;

		return ErrorCompilePixelShader;
	}

	result = mamain->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &PShader);

	code->Release();

	if (FAILED(result))
	{
		ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorCreatePixelShader, result);

		VShader->Release();
		VShader = 0;

		return ErrorCreatePixelShader;
	}

	return ErrorOk;
}
