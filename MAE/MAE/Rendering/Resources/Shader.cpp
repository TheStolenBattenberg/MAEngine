#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Rendering/Resources/ShaderImpl.h>
#include <MAE/Rendering/RendererImpl.h>

#include <cassert>

ShaderImpl::ShaderImpl(RendererImpl* renderer, const char* vertexshd, const char* pixelshd) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	this->renderer = renderer;

	HRESULT result;

	if (FAILED(D3DXCompileShader(vertexshd, strlen(vertexshd), NULL, NULL, "main", D3DXGetVertexShaderProfile(renderer->getDevice()), 0, &code, &err, &vtable))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		throw std::exception(error.c_str());
	}

	result = renderer->getDevice()->CreateVertexShader((DWORD*) code->GetBufferPointer(), &vshd);
	code->Release();

	if (FAILED(result))
		throw std::exception("Failed to create Vertex Shader");

	if (FAILED(D3DXCompileShader(pixelshd, strlen(pixelshd), NULL, NULL, "main", D3DXGetPixelShaderProfile(renderer->getDevice()), 0, &code, &err, &ptable))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		vshd->Release();
		vshd = 0;

		throw std::exception(error.c_str());
	}

	result = renderer->getDevice()->CreatePixelShader((DWORD*) code->GetBufferPointer(), &pshd);
	code->Release();

	if (FAILED(result)) {
		vshd->Release();
		vshd = 0;

		throw std::exception("Failed to create Pixel Shader");
	}
}

ShaderImpl::~ShaderImpl() {
	if (vtable != 0)
		vtable->Release();

	if (ptable != 0)
		ptable->Release();

	if (vshd != 0)
		vshd->Release();

	if (pshd != 0)
		pshd->Release();
}

uint ShaderImpl::find(const char* c) {
	Handles h = {
		vtable->GetConstantByName(0, c),
		ptable->GetConstantByName(0, c)
	};
	
	auto it = std::find(handles.begin(), handles.end(), h);

	if (it == handles.end()) {
		auto ind = handles.size();
		handles.push_back(h);
		return ind;
	}

	return it - handles.begin();
}

void ShaderImpl::setSampler(uint c, class Texture* sampler) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		renderer->setTexture(vtable->GetSamplerIndex(handles[c].vshd), sampler);

	if (handles[c].pshd)
		renderer->setTexture(vtable->GetSamplerIndex(handles[c].pshd), sampler);
}

uint ShaderImpl::getLocation(const char* str) {
	struct { const char* name; uint usage; } table[] = {
		{ "BINORMAL",     D3DDECLUSAGE_BINORMAL },
		{ "BLENDINDICES", D3DDECLUSAGE_BLENDINDICES },
		{ "BLENDWEIGHT",  D3DDECLUSAGE_BLENDWEIGHT },
		{ "COLOR",        D3DDECLUSAGE_COLOR },
		{ "NORMAL",       D3DDECLUSAGE_NORMAL },
		{ "POSITION",     D3DDECLUSAGE_POSITION },
		{ "POSITIONT",    D3DDECLUSAGE_POSITIONT },
		{ "PSIZE",        D3DDECLUSAGE_PSIZE },
		{ "TANGENT",      D3DDECLUSAGE_TANGENT },
		{ "TEXCOORD",     D3DDECLUSAGE_TEXCOORD }
	};

	auto end = str;

	for (; *end != 0 && isalpha(*end); ++end) { }

	auto ind = strtol(end, nullptr, 10);

	uint usage = 0;

	for (auto i : table) {
		if (strncmp(str, i.name, end - str) == 0) {
			usage = i.usage;
			break;
		}
	}

	return (ind << 16) | usage;
}

void ShaderImpl::setFloat(uint c, float f) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloat(renderer->getDevice(), handles[c].vshd, f);

	if (handles[c].pshd)
		vtable->SetFloat(renderer->getDevice(), handles[c].pshd, f);
}

void ShaderImpl::setVec2(uint c, const vec2& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setVec3(uint c, const vec3& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setVec4(uint c, const vec4& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setMat3(uint c, const mat3& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].vshd, v.data, v.size * v.size);

	if (handles[c].pshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].pshd, v.data, v.size * v.size);
}

void ShaderImpl::setMat4(uint c, const mat4& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].vshd, v.data, v.size * v.size);

	if (handles[c].pshd)
		vtable->SetFloatArray(renderer->getDevice(), handles[c].pshd, v.data, v.size * v.size);
}
