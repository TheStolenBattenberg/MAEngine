#include <MAE/Rendering/VertexData.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/VertexBuffer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_VertexDataCreate() {
	TRYBEG();
	return ptrToDouble(renderer->createVertexData());
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataSetVertexBuffer(double vd, double vb, double offset, double stride) {
	TRYBEG();
	doubleToPtr<VertexData>(vd)->setVertexBuffer(doubleToPtr<VertexBuffer>(vb), (uint) offset, (uint) stride);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataAddElement(double vd, double index, double type, double offset) {
	TRYBEG();
	doubleToPtr<VertexData>(vd)->addElement((uint) index, (uint) type, (uint) offset);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataBuild(double vd) {
	TRYBEG();
	renderer->buildVertexData(doubleToPtr<VertexData>(vd));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataSet(double vd) {
	TRYBEG();
	renderer->setVertexData(doubleToPtr<VertexData>(vd));
	return 1;
	TRYEND(0);
}
