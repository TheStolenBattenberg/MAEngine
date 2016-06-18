#include <MAE/Main.h>
#include <MAE/Rendering/VertexDecl.h>
#include <MAE/Core/Utils.h>

#include <MAE/GMLAPI/GMLMain.h>

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
		return mamain->setError(ErrorCreateVertexDecl);

	elems.clear();

	return ErrorOk;
}

void VertexDecl::set()
{
	mamain->d3ddev->SetVertexDeclaration(decl);
}
