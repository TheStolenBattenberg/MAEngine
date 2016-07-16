#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Renderer.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <Vec.h>
#include <Mat.h>

std::vector<float> matStack;

DLLEXPORT double MAE_ShaderCreate(const char* VSCode, const char* PSCode) {
	return ptrToDouble(renderer->createShader(VSCode, PSCode));
}

DLLEXPORT double MAE_ShaderSet(double s) {
	renderer->setShader(doubleToPtr<Shader>(s));

	return 1;
}

DLLEXPORT double MAE_ShaderReset() {
	renderer->setShader(nullptr);

	return 1;
}

DLLEXPORT double MAE_ShaderDestroy(double s) {
	delete doubleToPtr<Shader>(s);

	return 1;
}

DLLEXPORT double MAE_ShaderFindConstant(double s, const char* c) {
	return doubleToPtr<Shader>(s)->find(c);
}

DLLEXPORT double MAE_ShaderGetLocation(double s, const char* str) {
	return doubleToPtr<Shader>(s)->getLocation(str);
}

DLLEXPORT double MAE_ShaderSetSampler(double s, double c, double tex) {
	doubleToPtr<Shader>(s)->setSampler((uint) c, doubleToPtr<class Texture>(tex));

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantFloat(double s, double c, double x) {
	doubleToPtr<Shader>(s)->setFloat((uint) c, (float) x);

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantVec2(double s, double c, double x, double y) {
	doubleToPtr<Shader>(s)->setVec2((uint) c, vec2((float) x, (float) y));

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantVec3(double s, double c, double x, double y, double z) {
	doubleToPtr<Shader>(s)->setVec3((uint) c, vec3((float) x, (float) y, (float) z));

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantVec4(double s, double c, double x, double y, double z, double w) {
	doubleToPtr<Shader>(s)->setVec4((uint) c, vec4((float) x, (float) y, (float) z, (float) w));

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantMat3(double s, double c) {
	doubleToPtr<Shader>(s)->setMat3((uint) c, mat3(matStack.data()));

	return 1;
}

DLLEXPORT double MAE_ShaderSetConstantMat4(double s, double c) {
	doubleToPtr<Shader>(s)->setMat4((uint) c, mat4(matStack.data()));

	return 1;
}

DLLEXPORT double MADX9_MatStackFloat8(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8) {
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
}

DLLEXPORT double MADX9_MatStackFloat9(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9) {
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
}

DLLEXPORT double MADX9_MatStackClear() {
	matStack.clear();

	return 1;
}
