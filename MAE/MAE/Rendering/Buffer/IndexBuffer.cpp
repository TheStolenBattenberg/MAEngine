#include <MAE/Rendering/Buffer/IndexBufferImpl.h>

#include <MAE/Core/Exception.h>

#include <cassert>

IndexBufferImpl::IndexBufferImpl(uint length, uint fmt, const void* data, LPDIRECT3DDEVICE9 device) {
	D3DFORMAT table[] = {D3DFMT_INDEX16, D3DFMT_INDEX32};

	assert(("Unknown format", fmt <= 1));

	if (FAILED(device->CreateIndexBuffer(length, 0, table[fmt], D3DPOOL_DEFAULT, &ib, 0)))
		throw Exception("Failed to allocate VertexBuffer");

	if (data != nullptr)
		upload(data, 0, length);
}

IndexBufferImpl::~IndexBufferImpl() {
	ib->Release();
}

void* IndexBufferImpl::map(uint offset, uint size, uint flags) {
	void* ptr;

	if (FAILED(ib->Lock(offset, size, &ptr, 0)))
		throw Exception("Failed to map VertexBuffer");

	return ptr;
}

void IndexBufferImpl::unmap() {
	ib->Unlock();
}

void IndexBufferImpl::upload(const void* data, uint offset, uint size) {
	memcpy(map(offset, size, 0), data, size);
	unmap();
}
