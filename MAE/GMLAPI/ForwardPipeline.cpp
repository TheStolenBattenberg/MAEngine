#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <MAE/Rendering/Pipeline/ForwardPipeline.h>

DLLEXPORT double MAE_ForwardPipelineCreate() {
	TRYBEG();
	return ptrToDouble(new ForwardPipeline(renderer));
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineDestroy(double fp) {
	TRYBEG();
	delete doubleToPtr<ForwardPipeline>(fp);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineCreateModel(double fp, double draft, double dict) {
	TRYBEG();
	return ptrToDouble(doubleToPtr<ForwardPipeline>(fp)->createModel(doubleToPtr<ModelDraft>(draft), *doubleToPtr<TextureCollection>(dict)));
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineDestroyModel(double model) {
	TRYBEG();
	delete doubleToPtr<ModelBase>(model);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineRenderModel(double fp, double model) {
	TRYBEG();
	doubleToPtr<ForwardPipeline>(fp)->renderModel(doubleToPtr<ModelBase>(model));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineSetMVP(double fp) {
	TRYBEG();
	doubleToPtr<ForwardPipeline>(fp)->setMVP(mat4(matStack.data()));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ForwardPipelineSetNormal(double fp) {
	TRYBEG();
	doubleToPtr<ForwardPipeline>(fp)->setNormal(mat3(matStack.data()));
	return 1;
	TRYEND(0);
}
