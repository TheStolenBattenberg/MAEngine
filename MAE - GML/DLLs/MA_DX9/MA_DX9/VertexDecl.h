#pragma once

#include <d3d9.h>
#include <vector>

#include "Types.h"

class VertexDecl
{
public:
	~VertexDecl();

	void add(ushort stream, ushort offset, ubyte type, ubyte method, ubyte usage, ubyte usageIndex);
	bool build();
	void set();

private:
	std::vector<D3DVERTEXELEMENT9> elems;

	LPDIRECT3DVERTEXDECLARATION9 decl = 0;
};
