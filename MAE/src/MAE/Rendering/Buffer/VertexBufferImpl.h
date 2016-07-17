#pragma once

#include <MAE/Rendering/Buffer/VertexBuffer.h>

#include <d3d9.h>

class VertexBufferImpl: public VertexBuffer {
public:
	VertexBufferImpl(uint length, LPDIRECT3DDEVICE9 device);
	~VertexBufferImpl();

	void release();

	void* map(uint offset, uint size, uint flags);
	void unmap();
	void upload(const void* data, uint offset, uint size);

	inline LPDIRECT3DVERTEXBUFFER9 getVertexBuffer() {
		return vb;
	}

private:
	LPDIRECT3DVERTEXBUFFER9 vb;
};
