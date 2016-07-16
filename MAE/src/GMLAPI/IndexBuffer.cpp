#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/IndexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>
#include <GMLAPI/Stream.h>

DLLEXPORT double MAE_IndexBufferCreate(double size, double format) {
	return ptrToDouble(renderer->createIndexBuffer((uint) size, (uint) format));
}

DLLEXPORT double MAE_IndexBufferDestroy(double vb) {
	delete doubleToPtr<IndexBuffer>(vb);
	return 1;
}

DLLEXPORT double MAE_IndexBufferMap(double vb, double offset, double size, double flags) {
	auto stream = new MemoryStream(doubleToPtr<IndexBuffer>(vb)->map((uint) offset, (uint) size, (uint) flags));
	streams.add(stream);
	return ptrToDouble(stream);
}

DLLEXPORT double MAE_IndexBufferUnmap(double vb) {
	doubleToPtr<IndexBuffer>(vb)->unmap();
	return 1;
}

DLLEXPORT double MAE_IndexBufferUpload(double vb, const void* data, double offset, double size) {
	doubleToPtr<IndexBuffer>(vb)->upload(data, (uint) offset, (uint) size);
	return 1;
}
