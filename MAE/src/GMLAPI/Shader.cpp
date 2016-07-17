#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Renderer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <Vec.h>
#include <Mat.h>

std::vector<float> matStack;

DLLEXPORT double MAE_ShaderCreate(const char* VSCode, const char* PSCode) {
	TRYBEG();
	return ptrToDouble(renderer->createShader(VSCode, PSCode));
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSet(double s) {
	TRYBEG();
	renderer->setShader(doubleToPtr<Shader>(s));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderReset() {
	TRYBEG();
	renderer->setShader(nullptr);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderDestroy(double s) {
	TRYBEG();
	delete doubleToPtr<Shader>(s);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderFindConstant(double s, const char* c) {
	TRYBEG();
	return doubleToPtr<Shader>(s)->find(c);
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderGetLocation(double s, const char* str) {
	TRYBEG();
	return doubleToPtr<Shader>(s)->getLocation(str);
	TRYEND(-1);
}

DLLEXPORT double MAE_ShaderSetSampler(double s, double c, double tex) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setSampler((uint) c, doubleToPtr<Texture>(tex));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantFloat(double s, double c, double x) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setFloat((uint) c, (float) x);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantVec2(double s, double c, double x, double y) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setVec2((uint) c, vec2((float) x, (float) y));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantVec3(double s, double c, double x, double y, double z) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setVec3((uint) c, vec3((float) x, (float) y, (float) z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantVec4(double s, double c, double x, double y, double z, double w) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setVec4((uint) c, vec4((float) x, (float) y, (float) z, (float) w));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantMat3(double s, double c) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setMat3((uint) c, mat3(matStack.data()));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAE_ShaderSetConstantMat4(double s, double c) {
	TRYBEG();
	doubleToPtr<Shader>(s)->setMat4((uint) c, mat4(matStack.data()));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_MatStackFloat8(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8) {
	TRYBEG();
	matStack.reserve(8);

	matStack.push_back((float) v1);
	matStack.push_back((float) v2);
	matStack.push_back((float) v3);
	matStack.push_back((float) v4);
	matStack.push_back((float) v5);
	matStack.push_back((float) v6);
	matStack.push_back((float) v7);
	matStack.push_back((float) v8);

	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_MatStackFloat9(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9) {
	TRYBEG();
	matStack.reserve(9);

	matStack.push_back((float) v1);
	matStack.push_back((float) v2);
	matStack.push_back((float) v3);
	matStack.push_back((float) v4);
	matStack.push_back((float) v5);
	matStack.push_back((float) v6);
	matStack.push_back((float) v7);
	matStack.push_back((float) v8);
	matStack.push_back((float) v9);

	return 1;
	TRYEND(0);
}

DLLEXPORT double MADX9_MatStackClear() {
	TRYBEG();
	matStack.clear();
	return 1;
	TRYEND(0);
}
