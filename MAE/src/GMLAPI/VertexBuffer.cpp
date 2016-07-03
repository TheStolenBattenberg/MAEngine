#include <MAE/Main.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/VertexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Stream.h>
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

DLLEXPORT double MADX9_VertexBufferLock(double vb, double offset, double size, double flags) {
	auto stream = new MemoryStream(doubleToPtr<VertexBuffer>(vb)->map((uint) offset, (uint) size, (uint) flags));

	streams.add(stream);

	return ptrToDouble(stream);
}

DLLEXPORT double MAE_VertexBufferUnmap(double vb) {
	doubleToPtr<VertexBuffer>(vb)->unmap();

	return ErrorOk;
}

DLLEXPORT double MADX9_VertexBufferSet(double vb, double num, double offset, double stride)
{
	doubleToPtr<VertexBuffer>(vb)->set((uint) num, (uint) offset, (uint) stride);

	return 1;
}
