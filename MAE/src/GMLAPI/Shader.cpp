#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <Vec.h>
#include <Mat.h>

std::vector<float> matStack;
std::string err;

DLLEXPORT double MAE_ShaderCreate()
{
	Shader* s;

	auto ret = mamain->createShader(s);

	if (ret != ErrorOk)
		return ret;

	return ptrToDouble(s);
}

DLLEXPORT double MAE_ShaderCompileASM(double s, const char* VSCode, const char* PSCode)
{
	return doubleToPtr<Shader>(s)->compileASM(VSCode, PSCode, err);
}

DLLEXPORT double MAE_ShaderCompileHLSL9(double s, const char* VSCode, const char* PSCode)
{
	return doubleToPtr<Shader>(s)->compile(VSCode, PSCode, err);
}

DLLEXPORT double MADX9_ShaderSet(double s) {
	return mamain->setShader(doubleToPtr<Shader>(s));
}

DLLEXPORT double MAE_ShaderReset() {
	return mamain->resetShader();
}

DLLEXPORT double MADX9_ShaderDestroy(double s)
{
	delete doubleToPtr<Shader>(s);

	return ErrorOk;
}

DLLEXPORT double MADX9_ShaderFindConstant(double s, double type, const char* c)
{
	uint ind;

	auto ret = doubleToPtr<Shader>(s)->find((Shader::ShaderType) (uint) type, c, ind);

	return ret != ErrorOk ? ret : ind;
}

DLLEXPORT double MADX9_ShaderGetSampler(double s, double type, double c)
{
	uint ind;

	auto ret = doubleToPtr<Shader>(s)->getSampler((Shader::ShaderType) (uint) type, (uint) c, ind);

	return ret != ErrorOk ? ret : ind;
}

DLLEXPORT double MADX9_ShaderSetConstantFloat(double s, double type, double c, double x)
{
	return doubleToPtr<Shader>(s)->setFloat((Shader::ShaderType) (uint) type, (uint) c, (float) x);
}

DLLEXPORT double MADX9_ShaderSetConstantVec2(double s, double type, double c, double x, double y)
{
	return doubleToPtr<Shader>(s)->setVec2((Shader::ShaderType) (uint) type, (uint) c, vec2((float) x, (float) y));
}

DLLEXPORT double MADX9_ShaderSetConstantVec3(double s, double type, double c, double x, double y, double z)
{
	return doubleToPtr<Shader>(s)->setVec3((Shader::ShaderType) (uint) type, (uint) c, vec3((float) x, (float) y, (float) z));
}

DLLEXPORT double MADX9_ShaderSetConstantVec4(double s, double type, double c, double x, double y, double z, double w)
{
	return doubleToPtr<Shader>(s)->setVec4((Shader::ShaderType) (uint) type, (uint) c, vec4((float) x, (float) y, (float) z, (float) w));
}

DLLEXPORT double MADX9_ShaderSetConstantMat3(double s, double type, double c)
{
	return doubleToPtr<Shader>(s)->setMat3((Shader::ShaderType) (uint) type, (uint) c, mat3(matStack.data()));
}

DLLEXPORT double MADX9_ShaderSetConstantMat4(double s, double type, double c)
{
	return doubleToPtr<Shader>(s)->setMat4((Shader::ShaderType) (uint) type, (uint) c, mat4(matStack.data()));
}

DLLEXPORT double MADX9_MatStackFloat8(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8)
{
	matStack.reserve(8);

	matStack.push_back((float) v1);
	matStack.push_back((float) v2);
	matStack.push_back((float) v3);
	matStack.push_back((float) v4);
	matStack.push_back((float) v5);
	matStack.push_back((float) v6);
	matStack.push_back((float) v7);
	matStack.push_back((float) v8);

	return ErrorOk;
}

DLLEXPORT double MADX9_MatStackFloat9(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9)
{
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

	return ErrorOk;
}

DLLEXPORT double MADX9_MatStackClear()
{
	matStack.clear();

	return ErrorOk;
}
