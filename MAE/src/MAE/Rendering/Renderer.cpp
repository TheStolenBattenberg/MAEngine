#include <MAE/Rendering/RendererImpl.h>

#include <MAE/Rendering/IndexBufferImpl.h>
#include <MAE/Rendering/VertexBufferImpl.h>
#include <MAE/Rendering/VertexDataImpl.h>
#include <MAE/Rendering/Resources/ShaderImpl.h>
#include <MAE/Rendering/Resources/TextureImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>

void RendererImpl::release() {
	::delete this;
}

void RendererImpl::buildVertexData(VertexData* vd) {
	((VertexDataImpl*) vd)->build(device);
}

IndexBuffer* RendererImpl::createIndexBuffer(uint length, uint format) {
	return ::new IndexBufferImpl(length, format, device);
}

Scene* RendererImpl::createScene() {
	return ::new SceneImpl();
}

Shader* RendererImpl::createShader(const char* vshd, const char* pshd) {
	return ::new ShaderImpl(this, vshd, pshd);
}

Texture* RendererImpl::createTextureFromFile(const char* file, MipMaps mipmaps) {
	LPDIRECT3DTEXTURE9 tex;

	if (FAILED(D3DXCreateTextureFromFileEx(device, file, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw std::exception("Failed to load texture");

	return ::new TextureImpl(tex);
}

Texture* RendererImpl::createTextureFromFileInMemory(const void* data, uint length, MipMaps mipmaps) {
	LPDIRECT3DTEXTURE9 tex;

	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(device, data, length, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw std::exception("Failed to load texture");

	return ::new TextureImpl(tex);
}

VertexBuffer* RendererImpl::createVertexBuffer(uint length) {
	return ::new VertexBufferImpl(length, device);
}

VertexData* RendererImpl::createVertexData() {
	return ::new VertexDataImpl();
}

void RendererImpl::draw(uint type, uint index, uint count) {
	D3DPRIMITIVETYPE table[] = {
		D3DPT_POINTLIST,
		D3DPT_LINELIST,
		D3DPT_LINESTRIP,
		D3DPT_TRIANGLELIST,
		D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLEFAN
	};

	assert(("Invalid type", type < sizeof(table)));

	device->DrawPrimitive(table[type], index, count);
}

void RendererImpl::drawIndexed(uint type, uint count) {
	D3DPRIMITIVETYPE table[] = {
		D3DPT_POINTLIST,
		D3DPT_LINELIST,
		D3DPT_LINESTRIP,
		D3DPT_TRIANGLELIST,
		D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLEFAN
	};

	assert(("Invalid type", type < sizeof(table)));
	assert(("No VertexData set", vd != nullptr));

	device->DrawIndexedPrimitive(table[type], 0, 0, vd->getNumVertices(), 0, count);
}

void RendererImpl::setIndexBuffer(IndexBuffer* ib) {
	if (FAILED(device->SetIndices(((IndexBufferImpl*) ib)->getIndexBuffer())))
		throw std::exception("Failed to set IndexBuffer");
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

void RendererImpl::setVertexData(VertexData* vd) {
	(this->vd = (VertexDataImpl*) vd)->set(device);
}
