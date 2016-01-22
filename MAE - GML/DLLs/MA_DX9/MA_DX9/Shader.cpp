#include "Shader.h"
#include "Utils.h"
#include "MainImpl.h"
#include "ShaderImpl.h"

ShaderImpl::~ShaderImpl()
{
	if (vtable != 0)
		vtable->Release();

	if (ptable != 0)
		ptable->Release();

	if (vshd != 0)
		vshd->Release();

	if (pshd != 0)
		pshd->Release();

	main->shaderRemove(this);
}

uint ShaderImpl::release()
{
	if (--count == 0)
		delete this;

	return count;
}

ErrorCode ShaderImpl::compileASM(const std::string& vert, const std::string& pixel, std::string& error)
{
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	/**
	* Assemble Vertex Shader
	*/

	result = D3DXAssembleShader(vert.c_str(), vert.length(), NULL, NULL, 0, &code, &err);

	if (FAILED(result))
	{
		error = (char*) err->GetBufferPointer();
		err->Release();

		return main->setError(ErrorCompileVertexShader);
	}

	result = main->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &vshd);
	code->Release();

	if (FAILED(result))
		return main->setError(ErrorCreateVertexShader);

	/**
	* Assemble Pixel Shader
	*/

	result = D3DXAssembleShader(pixel.c_str(), pixel.length(), NULL, NULL, 0, &code, &err);

	if (FAILED(result))
	{
		error = (char*) err->GetBufferPointer();
		err->Release();

		vshd->Release();
		vshd = 0;

		return main->setError(ErrorCompilePixelShader);
	}

	result = main->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &pshd);
	code->Release();

	if (FAILED(result))
	{
		vshd->Release();
		vshd = 0;

		return main->setError(ErrorCreateVertexShader);
	}

	return ErrorOk;
}

ErrorCode ShaderImpl::compile(const std::string& vert, const std::string& pixel, std::string& error)
{
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	result = D3DXCompileShader(vert.c_str(), vert.length(), NULL, NULL, "main", D3DXGetVertexShaderProfile(main->d3ddev), 0, &code, &err, &vtable);

	if (FAILED(result))
	{
		error = (char*) err->GetBufferPointer();
		err->Release();

		return main->setError(ErrorCompileVertexShader);
	}

	result = main->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &vshd);

	code->Release();

	if (FAILED(result))
		return main->setError(ErrorCreateVertexShader);

	result = D3DXCompileShader(pixel.c_str(), pixel.length(), NULL, NULL, "main", D3DXGetPixelShaderProfile(main->d3ddev), 0, &code, &err, &ptable);

	if (FAILED(result))
	{
		error = (char*) err->GetBufferPointer();
		err->Release();

		vshd->Release();
		vshd = 0;

		return main->setError(ErrorCompilePixelShader);
	}

	result = main->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &pshd);

	code->Release();

	if (FAILED(result))
	{
		vshd->Release();
		vshd = 0;

		return main->setError(ErrorCreatePixelShader);
	}

	return ErrorOk;
}

ErrorCode ShaderImpl::find(ShaderType type, const std::string& c, uint& ind)
{
	auto table = type == ShaderTypeVertex ? vtable : ptable;

	if (table == 0)
		return main->setError(ErrorInv);

	D3DXHANDLE h = table->GetConstantByName(0, c.c_str());

	if (h == 0)
		return main->setError(ErrorInv);

	auto it = std::find(handles.begin(), handles.end(), h);

	if (it != handles.end())
		ind = it - handles.begin();
	else
	{
		ind = handles.size();
		handles.push_back(h);
	}

	return ErrorOk;
}

ErrorCode ShaderImpl::getSampler(ShaderType type, uint c, uint& ind)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	ind = (type == ShaderTypeVertex ? vtable : ptable)->GetSamplerIndex(handles[c]);
	
	return ErrorOk;
}

ErrorCode ShaderImpl::getVertexShader(LPDIRECT3DVERTEXSHADER9& vert)
{
	if (vshd == 0)
		return main->setError(ErrorInv);

	vshd->AddRef();
	vert = vshd;

	return ErrorOk;
}

ErrorCode ShaderImpl::getPixelShader(LPDIRECT3DPIXELSHADER9& pixel)
{
	if (pshd == 0)
		return main->setError(ErrorInv);

	pshd->AddRef();
	pixel = pshd;

	return ErrorOk;
}

ErrorCode ShaderImpl::setFloat(ShaderType type, uint c, float f)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloat(main->d3ddev, handles[c], f);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode ShaderImpl::setVec2(ShaderType type, uint c, const vec2& v)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloatArray(main->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode ShaderImpl::setVec3(ShaderType type, uint c, const vec3& v)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloatArray(main->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode ShaderImpl::setVec4(ShaderType type, uint c, const vec4& v)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloatArray(main->d3ddev, handles[c], v.data, v.components);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode ShaderImpl::setMat3(ShaderType type, uint c, const mat3& v)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloatArray(main->d3ddev, handles[c], v.data, v.size * v.size);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode ShaderImpl::setMat4(ShaderType type, uint c, const mat4& v)
{
	if (c >= handles.size())
		return main->setError(ErrorInv);

	HRESULT res = (type == ShaderTypeVertex ? vtable : ptable)->SetFloatArray(main->d3ddev, handles[c], v.data, v.size * v.size);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}
