#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/VertexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>
#include <GMLAPI/Stream.h>

DLLEXPORT double MAE_VertexBufferCreate(double size) {
	return ptrToDouble(renderer->createVertexBuffer((uint) size));
}

DLLEXPORT double MAE_VertexBufferDestroy(double vb) {
	delete doubleToPtr<VertexBuffer>(vb);
	return 1;
}

DLLEXPORT double MAE_VertexBufferMap(double vb, double offset, double size, double flags) {
	auto stream = new MemoryStream(doubleToPtr<VertexBuffer>(vb)->map((uint) offset, (uint) size, (uint) flags));
	streams.add(stream);
	return ptrToDouble(stream);
}

DLLEXPORT double MAE_VertexBufferUnmap(double vb) {
	doubleToPtr<VertexBuffer>(vb)->unmap();
	return 1;
}

DLLEXPORT double MAE_VertexBufferUpload(double vb, const void* data, double offset, double size) {
	doubleToPtr<VertexBuffer>(vb)->upload(data, (uint) offset, (uint) size);
	return 1;
}
