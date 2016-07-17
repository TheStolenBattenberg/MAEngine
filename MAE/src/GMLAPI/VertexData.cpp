#include <MAE/Rendering/VertexData.h>

#include <MAE/Rendering/Buffer/IndexBuffer.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/Buffer/VertexBuffer.h>
#include <MAE/Rendering/VertexDataBuilder.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_VertexDataCreate(double vdb) {
	TRYBEG();
	return ptrToDouble(renderer->createVertexData(doubleToPtr<VertexDataBuilder>(vdb)));
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataDestroy(double vd) {
	TRYBEG();
	delete doubleToPtr<VertexData>(vd);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataReplaceVertexBuffer(double vd, double old, double replacement) {
	TRYBEG();
	doubleToPtr<VertexData>(vd)->replaceVertexBuffer(doubleToPtr<VertexBuffer>(old), doubleToPtr<VertexBuffer>(replacement));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataSetIndexBuffer(double vd, double ib) {
	TRYBEG();
	doubleToPtr<VertexData>(vd)->setIndexBuffer(doubleToPtr<IndexBuffer>(ib));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_VertexDataSet(double vd) {
	TRYBEG();
	renderer->setVertexData(doubleToPtr<VertexData>(vd));
	return 1;
	TRYEND(0);
}
