#include <MAE/Main.h>
#include <MAE/Rendering/VertexDecl.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_VertexDeclarationCreate()
{
	auto decl = new VertexDecl;

	mamain->VertexDeclarations.add(decl);

	return ptrToDouble(decl);
}

DLLEXPORT double MADX9_VertexDeclarationDestroy(double decl)
{
	auto ptr = doubleToPtr<VertexDecl>(decl);

	mamain->VertexDeclarations.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MADX9_VertexDeclarationAdd(double decl, double stream, double offset, double type, double method, double usage, double usageIndex)
{
	doubleToPtr<VertexDecl>(decl)->add((ushort) stream, (ushort) offset, (ubyte) type, (ubyte) method, (ubyte) usage, (ubyte) usageIndex);

	return 1;
}

DLLEXPORT double MADX9_VertexDeclarationBuild(double decl)
{
	return doubleToPtr<VertexDecl>(decl)->build();
}

DLLEXPORT double MADX9_VertexDeclarationSet(double decl)
{
	doubleToPtr<VertexDecl>(decl)->set();

	return 1;
}
