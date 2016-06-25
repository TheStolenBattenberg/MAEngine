#include <MAE/Main.h>
#include <MAE/Core/Types.h>
#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/Core/Utils.h>

#include <GMLAPI/Main.h>

#include <Vec.h>
#include <Mat.h>

std::vector<float> matStack;
std::string err;

DLLEXPORT double MAE_ShaderCreate()
{
	Shader* s;

	ErrorCode ret = mamain->createShader(s);

	return ret != ErrorOk ? ret : VectorPushBackPointer(s, shaders);
}

DLLEXPORT double MAE_ShaderCompileASM(double index, const char* VSCode, const char* PSCode)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->compileASM(VSCode, PSCode, err);
}

DLLEXPORT double MAE_ShaderCompileHLSL9(double index, const char* VSCode, const char* PSCode)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->compile(VSCode, PSCode, err);
}

DLLEXPORT double MADX9_ShaderSet(double index)
{
	if (index < 0)
		return mamain->resetShader();

	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return mamain->setShader(shd);
}

DLLEXPORT double MADX9_ShaderDestroy(double index)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	shd->release();
	shaders[(uint) index] = 0;

	return ErrorOk;
}

DLLEXPORT double MADX9_ShaderFindConstant(double index, double type, const char* c)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	uint ind;

	ErrorCode ret = shd->find((Shader::ShaderType) (uint) type, c, ind);

	return ret != ErrorOk ? ret : ind;
}

DLLEXPORT double MADX9_ShaderGetSampler(double index, double type, double c)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	uint ind;

	ErrorCode ret = shd->getSampler((Shader::ShaderType) (uint) type, (uint) c, ind);

	return ret != ErrorOk ? ret : ind;
}

DLLEXPORT double MADX9_ShaderSetConstantFloat(double index, double type, double c, double x)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setFloat((Shader::ShaderType) (uint) index, (uint) c, (float) x);
}

DLLEXPORT double MADX9_ShaderSetConstantVec2(double index, double type, double c, double x, double y)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setVec2((Shader::ShaderType) (uint) index, (uint) c, vec2((float) x, (float) y));
}

DLLEXPORT double MADX9_ShaderSetConstantVec3(double index, double type, double c, double x, double y, double z)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setVec3((Shader::ShaderType) (uint) index, (uint) c, vec3((float) x, (float) y, (float) z));
}

DLLEXPORT double MADX9_ShaderSetConstantVec4(double index, double type, double c, double x, double y, double z, double w)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setVec4((Shader::ShaderType) (uint) index, (uint) c, vec4((float) x, (float) y, (float) z, (float) w));
}

DLLEXPORT double MADX9_ShaderSetConstantMat3(double index, double type, double c)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setMat3((Shader::ShaderType) (uint) index, (uint) c, mat3(matStack.data()));
}

DLLEXPORT double MADX9_ShaderSetConstantMat4(double index, double type, double c)
{
	Shader* shd = VectorGetPointerSafe((uint) index, shaders);

	if (shd == 0)
		return mamain->setError(ErrorInv);

	return shd->setMat4((Shader::ShaderType) (uint) index, (uint) c, mat4(matStack.data()));
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
