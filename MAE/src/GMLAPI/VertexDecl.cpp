#include <MAE/Main.h>
#include <MAE/Rendering/VertexDecl.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>

DLLEXPORT double MADX9_VertexDeclarationCreate()
{
	try
	{
		return putInto(new VertexDecl(), mamain->VertexDeclarations);
	}
	catch (std::exception)
	{
		return -1;
	}
}

DLLEXPORT double MADX9_VertexDeclarationDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->VertexDeclarations))
		return 0;

	delete mamain->VertexDeclarations[(uint) ind];
	mamain->VertexDeclarations[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_VertexDeclarationAdd(double ind, double stream, double offset, double type, double method, double usage, double usageIndex)
{
	if (!isValidIndex((uint) ind, mamain->VertexDeclarations))
		return 0;

	mamain->VertexDeclarations[(uint) ind]->add((ushort) ind, (ushort) stream, (ubyte) type, (ubyte) method, (ubyte) usage, (ubyte) usageIndex);

	return 1;
}

DLLEXPORT double MADX9_VertexDeclarationBuild(double ind)
{
	if (!isValidIndex((uint) ind, mamain->VertexDeclarations))
		return 0;

	return mamain->VertexDeclarations[(uint) ind]->build();
}

DLLEXPORT double MADX9_VertexDeclarationSet(double ind)
{
	if (!isValidIndex((uint) ind, mamain->VertexDeclarations))
		return 0;

	mamain->VertexDeclarations[(uint) ind]->set();

	return 1;
}
