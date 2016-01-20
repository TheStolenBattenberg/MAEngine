#include "Main.h"
#include "Types.h"
#include "Shader.h"
#include "Utils.h"

#include "MA_Main.h"

#include <Vec.h>
#include <Mat.h>

std::vector<float> matStack;

DLLEXPORT double MADX9_ShaderCreateASM(const char* VSCode, const char* PSCode)
{
	Shader* shd = new Shader();

	ErrorCode ret = shd->compileASM(VSCode, PSCode);

	if (ret != ErrorOk)
	{
		delete shd;
		return ret;
	}

	return putInto(shd, mamain->Shader);
}

DLLEXPORT double MADX9_ShaderCreateHLSL9(const char* VSCode, const char* PSCode)
{
	Shader* shd = new Shader();

	ErrorCode ret = shd->compile(VSCode, PSCode);

	if (ret != ErrorOk)
	{
		delete shd;
		return ret;
	}

	return putInto(shd, mamain->Shader);
}

DLLEXPORT double MADX9_ShaderSet(double index)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT result;

	mamain->d3ddev->GetFVF(&mamain->stFVF);

	result = mamain->d3ddev->SetVertexShader(mamain->Shader[(uint)index]->VShader);

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, result, "SetVertexShader");

	result = mamain->d3ddev->SetPixelShader(mamain->Shader[(uint)index]->PShader);

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, result, "SetPixelShader");

	return ErrorOk;
}

DLLEXPORT double MADX9_ShaderReset()
{
	HRESULT result;

	result = mamain->d3ddev->SetVertexShader(NULL);

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, result, "SetVertexShader");

	result = mamain->d3ddev->SetPixelShader(NULL);

	if (FAILED(result))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, result, "SetPixelShader");

	mamain->d3ddev->SetFVF(mamain->stFVF);
	return ErrorOk;
}

DLLEXPORT double MADX9_ShaderDestroy(double index)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	delete mamain->Shader[(uint)index];
	mamain->Shader[(uint)index] = 0;

	return ErrorOk;
}

DLLEXPORT double MADX9_ShaderFindConstant(double index, double shd, const char* c)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	uint ind;

	ErrorCode ret = (shd ? mamain->Shader[(uint)index]->PConstants : mamain->Shader[(uint)index]->VConstants).find(c, ind);

	if (ret != ErrorOk)
		return ret;

	return ind;
}

DLLEXPORT double MADX9_ShaderGetSampler(double index, double shd, double c)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	uint ind;

	ErrorCode ret = (shd ? mamain->Shader[(uint)index]->PConstants : mamain->Shader[(uint)index]->VConstants).getSampler((uint) c, ind);

	if (ret != ErrorOk)
		return ret;

	return ind;
}

DLLEXPORT double MADX9_ShaderSetConstantFloat(double index, double shd, double c, double x)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setFloat((uint) c, (float) x);
}

DLLEXPORT double MADX9_ShaderSetConstantVec2(double index, double shd, double c, double x, double y)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setVec2((uint) c, vec2((float) x, (float) y));
}

DLLEXPORT double MADX9_ShaderSetConstantVec3(double index, double shd, double c, double x, double y, double z)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setVec3((uint) c, vec3((float) x, (float) y, (float) z));
}

DLLEXPORT double MADX9_ShaderSetConstantVec4(double index, double shd, double c, double x, double y, double z, double w)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setVec4((uint) c, vec4((float) x, (float) y, (float) z, (float) w));
}

DLLEXPORT double MADX9_ShaderSetConstantMat3(double index, double shd, double c)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setMat3((uint)c, mat3(matStack.data()));
}

DLLEXPORT double MADX9_ShaderSetConstantMat4(double index, double shd, double c)
{
	if (!isValidIndex((uint) index, mamain->Shader))
		return ErrorHandle(mamain->err, ErrorInv);

	return (shd ? mamain->Shader[(uint) index]->PConstants : mamain->Shader[(uint) index]->VConstants).setMat4((uint)c, mat4(matStack.data()));
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
