#include <MAE/Rendering/VertexBuffer.h>
#include <MAE/Main.h>

VertexBuffer::VertexBuffer(uint length, uint usage, D3DPOOL pool)
{
	// TODO: Add error checking
	mainObj->d3ddev->CreateVertexBuffer(length, usage, 0, pool, &vb, 0);
}

VertexBuffer::~VertexBuffer() {
	if (vb != 0)
		vb->Release();
}

void* VertexBuffer::map(uint offset, uint size, uint flags) {
	void* ptr;

	if (FAILED(vb->Lock(offset, size, &ptr, flags)))
		return nullptr;

	return ptr;
}

void VertexBuffer::unmap() {
	vb->Unlock();
}

void VertexBuffer::set(uint num, uint offset, uint stride) {
	mainObj->d3ddev->SetStreamSource(num, vb, offset, stride);
}
