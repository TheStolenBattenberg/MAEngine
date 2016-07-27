#include <MAE/Rendering/RendererImpl.h>

#include <MAE/Rendering/Buffer/IndexBufferImpl.h>
#include <MAE/Rendering/Resources/ShaderImpl.h>
#include <MAE/Rendering/Resources/TextureImpl.h>
#include <MAE/Rendering/Buffer/VertexBufferImpl.h>
#include <MAE/Rendering/VertexDataImpl.h>

RendererImpl::~RendererImpl() { }

IndexBuffer* RendererImpl::createIndexBuffer(uint length, uint format, const void* data) {
	return new IndexBufferImpl(length, format, data, device);
}

Shader* RendererImpl::createShader(const char* vshd, const char* pshd) {
	assert(("Invalid string", vshd != nullptr && pshd != nullptr));

	return new ShaderImpl(this, vshd, pshd);
}

Texture* RendererImpl::createTextureFromFile(const char* file, uint mipmaps) {
	assert(("Invalid string", file != nullptr));

	LPDIRECT3DTEXTURE9 tex;

	if (FAILED(D3DXCreateTextureFromFileEx(device, file, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw std::exception("Failed to load texture");

	return new TextureImpl(tex);
}

Texture* RendererImpl::createTextureFromFileInMemory(const void* data, uint length, uint mipmaps) {
	assert(("Invalid data", data != nullptr));

	LPDIRECT3DTEXTURE9 tex;

	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(device, data, length, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw std::exception("Failed to load texture");

	return new TextureImpl(tex);
}

VertexBuffer* RendererImpl::createVertexBuffer(uint length, const void* data) {
	return new VertexBufferImpl(length, data, device);
}

VertexData* RendererImpl::createVertexData() {
	return new VertexDataImpl(device);
}

VertexData* RendererImpl::copyVertexData(VertexData* vd) {
	return new VertexDataImpl(*(VertexDataImpl*) vd);
}

void RendererImpl::draw(VertexData* vd, uint type, uint index, uint count) {
	D3DPRIMITIVETYPE table[] = {
		D3DPT_POINTLIST,
		D3DPT_LINELIST,
		D3DPT_LINESTRIP,
		D3DPT_TRIANGLELIST,
		D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLEFAN
	};

	assert(("Invalid type", type < sizeof(table)));
	assert(("Invalid VertexData", vd != nullptr));

	((VertexDataImpl*) vd)->set();
	device->DrawPrimitive(table[type], index, count);
	((VertexDataImpl*) vd)->reset();
}

void RendererImpl::drawIndexed(VertexData* vd, uint type, uint count) {
	D3DPRIMITIVETYPE table[] = {
		D3DPT_POINTLIST,
		D3DPT_LINELIST,
		D3DPT_LINESTRIP,
		D3DPT_TRIANGLELIST,
		D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLEFAN
	};

	assert(("Invalid type", type < sizeof(table)));
	assert(("Invalid VertexData", vd != nullptr));

	((VertexDataImpl*) vd)->setInd();
	device->DrawIndexedPrimitive(table[type], 0, 0, ((VertexDataImpl*) vd)->getNumVertices(), 0, count);
	((VertexDataImpl*) vd)->resetInd();
}

void RendererImpl::setShader(Shader* shd) {
	if (shd != nullptr) {
		device->SetVertexShader(((ShaderImpl*) shd)->getVertexShader());
		device->SetPixelShader(((ShaderImpl*) shd)->getPixelShader());
	}
	else {
		device->SetVertexShader(nullptr);
		device->SetPixelShader(nullptr);
	}
}

void RendererImpl::setTexture(uint stage, Texture* tex) {
	device->SetTexture(stage, tex == nullptr ? nullptr : ((TextureImpl*) tex)->getTexture());
}
