#include <MAE/Rendering/VertexDataBuilder.h>

#include <MAE/Rendering/IndexBuffer.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/VertexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_VertexDataBuilderCreate() {
	TRYBEG();
	return ptrToDouble(renderer->createVertexDataBuilder());
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataBuilderDestroy(double vdb) {
	TRYBEG();
	delete doubleToPtr<VertexDataBuilder>(vdb);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataBuilderSetIndexBuffer(double vd, double ib) {
	TRYBEG();
	doubleToPtr<VertexDataBuilder>(vd)->setIndexBuffer(doubleToPtr<IndexBuffer>(ib));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataBuilderSetVertexBuffer(double vd, double vb, double offset, double stride) {
	TRYBEG();
	doubleToPtr<VertexDataBuilder>(vd)->setVertexBuffer(doubleToPtr<VertexBuffer>(vb), (uint) offset, (uint) stride);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataBuilderAddElement(double vd, double index, double type, double offset) {
	TRYBEG();
	doubleToPtr<VertexDataBuilder>(vd)->addElement((uint) index, (uint) type, (uint) offset);
	return 1;
	TRYEND(0);
}
