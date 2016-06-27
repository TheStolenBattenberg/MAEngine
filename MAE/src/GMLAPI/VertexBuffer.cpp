#include <MAE/Main.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/VertexBuffer.h>
#include <MAE/Core/Buffer.h>
#include <MAE/Core/Memory.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MADX9_VertexBufferCreate(double length, double usage, double pool)
{
	auto vb = new VertexBuffer((uint) length, (uint) usage, (D3DPOOL) (uint) pool);

	mamain->VertexBuffers.add(vb);

	return ptrToDouble(vb);
}

DLLEXPORT double MADX9_VertexBufferDestroy(double vb)
{
	auto ptr = doubleToPtr<VertexBuffer>(vb);

	mamain->VertexBuffers.remove(ptr);
	delete ptr;

	return 1;
}

DLLEXPORT double MADX9_VertexBufferLock(double vb, double offset, double size, double flags)
{
	auto buffer = new Buffer(doubleToPtr<VertexBuffer>(vb)->createMemoryInterface((uint) offset, (uint) size, (uint) flags));

	mamain->Buffers.add(buffer);

	return ptrToDouble(buffer);
}

DLLEXPORT double MADX9_VertexBufferSet(double vb, double num, double offset, double stride)
{
	doubleToPtr<VertexBuffer>(vb)->set((uint) num, (uint) offset, (uint) stride);

	return 1;
}
