#include "VertexBuffer.h"
#include "Main.h"

VertexBuffer::VertexBuffer(uint length, uint usage, D3DPOOL pool)
{
	HRESULT res = mamain->d3ddev->CreateVertexBuffer(length, usage, 0, pool, &vb, 0);

	if (FAILED(res))
		mamain->err.onErrorDX9("Failed to create vertex buffer", res);
}

VertexBuffer::~VertexBuffer()
{
	if (vb != 0)
		vb->Release();
}

Memory* VertexBuffer::createMemoryInterface(uint offset, uint size, uint flags)
{
	void* ptr;

	HRESULT res = vb->Lock(offset, size, &ptr, flags);

	if (FAILED(res))
	{
		mamain->err.onErrorDX9("Failed to lock vertex buffer", res);
		return 0;
	}

	FixedMemory* m = new FixedMemory(ptr, size, flags & D3DLOCK_READONLY ? FixedMemory::FlagReadOnly : 0);

	m->onFree([](void* vb)
	{
		((LPDIRECT3DVERTEXBUFFER9) vb)->Unlock();
	}, vb);

	return m;
}

void VertexBuffer::set(uint num, uint offset, uint stride)
{
	mamain->d3ddev->SetStreamSource(num, vb, offset, stride);
}
