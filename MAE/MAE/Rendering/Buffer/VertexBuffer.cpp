#include <MAE/Rendering/Buffer/VertexBufferImpl.h>

#include <exception>

VertexBufferImpl::VertexBufferImpl(uint length, const void* data, LPDIRECT3DDEVICE9 device) {
	if (FAILED(device->CreateVertexBuffer(size = length, 0, 0, D3DPOOL_DEFAULT, &vb, 0)))
		throw std::exception("Failed to allocate VertexBuffer");

	if (data != nullptr)
		upload(data, 0, length);
}

VertexBufferImpl::~VertexBufferImpl() {
	vb->Release();
}

void* VertexBufferImpl::map(uint offset, uint size, uint flags) {
	void* ptr;

	if (FAILED(vb->Lock(offset, size, &ptr, 0)))
		throw std::exception("Failed to map VertexBuffer");

	return ptr;
}

void VertexBufferImpl::unmap() {
	vb->Unlock();
}

void VertexBufferImpl::upload(const void* data, uint offset, uint size) {
	memcpy(map(offset, size, 0), data, size);
	unmap();
}
