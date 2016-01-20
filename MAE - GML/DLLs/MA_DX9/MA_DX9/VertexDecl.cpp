#include "Main.h"
#include "VertexDecl.h"
#include "Utils.h"

#include "MA_Main.h"

VertexDecl::~VertexDecl()
{
	if (decl != 0)
		decl->Release();
}

void VertexDecl::add(ushort stream, ushort offset, ubyte type, ubyte method, ubyte usage, ubyte usageIndex)
{
	elems.push_back({stream, offset, type, method, usage, usageIndex});
}

ErrorCode VertexDecl::build()
{
	elems.push_back(D3DDECL_END());

	HRESULT res = mamain->d3ddev->CreateVertexDeclaration(elems.data(), &decl);

	if (FAILED(res))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, res);

	elems.clear();

	return ErrorOk;
}

void VertexDecl::set()
{
	mamain->d3ddev->SetVertexDeclaration(decl);
}
