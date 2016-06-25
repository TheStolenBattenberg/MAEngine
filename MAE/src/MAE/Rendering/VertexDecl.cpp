#include <MAE/Main.h>
#include <MAE/Rendering/VertexDecl.h>
#include <MAE/Core/Utils.h>

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

	HRESULT res = mainObj->d3ddev->CreateVertexDeclaration(elems.data(), &decl);

	if (FAILED(res))
		return mainObj->setError(ErrorCreateVertexDecl);

	elems.clear();

	return ErrorOk;
}

void VertexDecl::set()
{
	mainObj->d3ddev->SetVertexDeclaration(decl);
}
