#include <MAE/Rendering/VertexBuffer.h>
#include <MAE/Main.h>

#include <MAE/GMLAPI/GMLMain.h>

VertexBuffer::VertexBuffer(uint length, uint usage, D3DPOOL pool)
{
	// TODO: Add error checking
	mamain->d3ddev->CreateVertexBuffer(length, usage, 0, pool, &vb, 0);
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

	// TODO: Add error checking

	if (FAILED(res))
	{
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
