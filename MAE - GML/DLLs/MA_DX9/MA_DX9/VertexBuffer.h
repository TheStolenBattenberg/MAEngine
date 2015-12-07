#pragma once

#include <d3d9.h>

#include "Memory.h"
#include "Types.h"

class VertexBuffer
{
public:
	VertexBuffer(uint length, uint usage, D3DPOOL pool);
	~VertexBuffer();

	Memory* createMemoryInterface(uint offset, uint size, uint flags);
	void set(uint num, uint offset, uint stride);

private:
	LPDIRECT3DVERTEXBUFFER9 vb = 0;
};
