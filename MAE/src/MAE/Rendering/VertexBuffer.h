#pragma once

#include <d3d9.h>

#include <MAE/Core/Types.h>

class VertexBuffer
{
public:
	VertexBuffer(uint length, uint usage, D3DPOOL pool);
	~VertexBuffer();

	void* map(uint offset, uint size, uint flags);
	void unmap();
	void set(uint num, uint offset, uint stride);

private:
	LPDIRECT3DVERTEXBUFFER9 vb = 0;
};
