#include "Main.h"
#include "VertexDecl.h"

VertexDecl::~VertexDecl()
{
	if (decl != 0)
		decl->Release();
}

void VertexDecl::add(ushort stream, ushort offset, ubyte type, ubyte method, ubyte usage, ubyte usageIndex)
{
	D3DVERTEXELEMENT9 elem = {stream, offset, type, method, usage, usageIndex};
	elems.push_back(elem);
}

bool VertexDecl::build()
{
	D3DVERTEXELEMENT9 elem = D3DDECL_END();
	elems.push_back(elem);

	HRESULT res = mamain->d3ddev->CreateVertexDeclaration(elems.data(), &decl);

	if (FAILED(res))
	{
		mamain->err.onErrorDX9("Failed to create vertex declaration", res);
		return 0;
	}

	elems.clear();

	return 1;
}

void VertexDecl::set()
{
	mamain->d3ddev->SetVertexDeclaration(decl);
}
