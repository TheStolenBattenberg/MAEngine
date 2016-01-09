#pragma once

#include "Types.h"

#include <d3d9.h>
#include <vector>

class VertexDecl
{
public:
	~VertexDecl();

	void add(ushort stream, ushort offset, ubyte type, ubyte method, ubyte usage, ubyte usageIndex);
	ErrorCode build();
	void set();

private:
	std::vector<D3DVERTEXELEMENT9> elems;

	LPDIRECT3DVERTEXDECLARATION9 decl = 0;
};
