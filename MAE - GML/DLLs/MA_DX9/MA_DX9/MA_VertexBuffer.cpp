#include "Main.h"
#include "Utils.h"
#include "VertexBuffer.h"
#include "Buffer.h"
#include "Memory.h"

DLLEXPORT double MADX9_VertexBufferCreate(double length, double usage, double pool)
{
	try
	{
		return putInto(new VertexBuffer((uint) length, (uint) usage, (D3DPOOL) (uint) pool), mamain->VertexBuffers);
	}
	catch (std::exception)
	{
		return -1;
	}
}

DLLEXPORT double MADX9_VertexBufferDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->VertexBuffers))
		return 0;

	delete mamain->VertexBuffers[(uint) ind];
	mamain->VertexBuffers[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_VertexBufferLock(double ind, double offset, double size, double flags)
{
	if (!isValidIndex((uint) ind, mamain->VertexBuffers))
		return 0;

	try
	{
		return putInto(new Buffer(mamain->VertexBuffers[(uint) ind]->createMemoryInterface((uint) offset, (uint) size, (uint) flags)), mamain->Buffers);
	}
	catch (std::exception)
	{
		return -1;
	}
}

DLLEXPORT double MADX9_VertexBufferSet(double ind, double num, double offset, double stride)
{
	if (!isValidIndex((uint) ind, mamain->VertexBuffers))
		return 0;

	mamain->VertexBuffers[(uint) ind]->set((uint) num, (uint) offset, (uint) stride);

	return 1;
}
