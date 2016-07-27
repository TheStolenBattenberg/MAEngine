#pragma once

#include <MAE/Rendering/Buffer/IndexBuffer.h>

#include <d3d9.h>

class IndexBufferImpl: public IndexBuffer {
public:
	IndexBufferImpl(uint length, uint fmt, const void* data, LPDIRECT3DDEVICE9 device);
	~IndexBufferImpl();

	void* map(uint offset, uint size, uint flags);
	void unmap();
	void upload(const void* data, uint offset, uint size);

	inline LPDIRECT3DINDEXBUFFER9 getIndexBuffer() {
		return ib;
	}

private:
	LPDIRECT3DINDEXBUFFER9 ib;
};
