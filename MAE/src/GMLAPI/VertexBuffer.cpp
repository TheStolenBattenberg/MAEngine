#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/VertexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>
#include <GMLAPI/Stream.h>

DLLEXPORT double MAE_VertexBufferCreate(double size) {
	TRYBEG();
	return ptrToDouble(renderer->createVertexBuffer((uint) size));
	TRYEND(0);
}

DLLEXPORT double MAE_VertexBufferDestroy(double vb) {
	TRYBEG();
	delete doubleToPtr<VertexBuffer>(vb);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexBufferMap(double vb, double offset, double size, double flags) {
	TRYBEG();
	auto stream = new MemoryStream(doubleToPtr<VertexBuffer>(vb)->map((uint) offset, (uint) size, (uint) flags));
	streams.add(stream);
	return ptrToDouble(stream);
	TRYEND(0);
}

DLLEXPORT double MAE_VertexBufferUnmap(double vb) {
	TRYBEG();
	doubleToPtr<VertexBuffer>(vb)->unmap();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexBufferUpload(double vb, const void* data, double offset, double size) {
	TRYBEG();
	doubleToPtr<VertexBuffer>(vb)->upload(data, (uint) offset, (uint) size);
	return 1;
	TRYEND(0);
}
