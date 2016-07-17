#include <MAE/Rendering/VertexData.h>

#include <MAE/Rendering/Renderer.h>
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

DLLEXPORT double MAE_VertexDataSet(double vd) {
	TRYBEG();
	renderer->setVertexData(doubleToPtr<VertexData>(vd));
	return 1;
	TRYEND(0);
}
