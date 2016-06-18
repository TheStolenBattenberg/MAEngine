#pragma once

#include <MAE/Main.h>
#include <MAE/Core/Types.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Mat.h>
#include <Vec.h>

#include <MAE/Core/RefCounted.h>

class Shader: public RefCounted
{
public:
	enum ShaderType: long
	{
		ShaderTypeVertex = 0,
		ShaderTypePixel  = 1
	};

	virtual uint release() = 0;

	virtual ErrorCode compile(const std::string& vert, const std::string& pixel, std::string& error) = 0;
	virtual ErrorCode compileASM(const std::string& vert, const std::string& pixel, std::string& error) = 0;

	virtual ErrorCode find(ShaderType type, const std::string& c, uint& ind) = 0;
	virtual ErrorCode getSampler(ShaderType type, uint c, uint& ind) = 0;

	virtual ErrorCode getVertexShader(LPDIRECT3DVERTEXSHADER9& vert) = 0;
	virtual ErrorCode getPixelShader(LPDIRECT3DPIXELSHADER9& pixel) = 0;

	virtual ErrorCode setFloat(ShaderType type, uint c, float f) = 0;
	virtual ErrorCode setVec2(ShaderType type, uint c, const vec2& v) = 0;
	virtual ErrorCode setVec3(ShaderType type, uint c, const vec3& v) = 0;
	virtual ErrorCode setVec4(ShaderType type, uint c, const vec4& v) = 0;
	virtual ErrorCode setMat3(ShaderType type, uint c, const mat3& m) = 0;
	virtual ErrorCode setMat4(ShaderType type, uint c, const mat4& m) = 0;
};
