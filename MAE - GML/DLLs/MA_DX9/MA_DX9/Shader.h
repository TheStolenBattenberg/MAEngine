#pragma once

#include "Main.h"
#include "Types.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <Mat.h>
#include <Vec.h>

class Shader
{
public:
	class ShaderConstants
	{
	public:
		~ShaderConstants();

		ErrorCode find(const std::string& c, uint& ind);
		ErrorCode getSampler(uint c, uint& ind);

		ErrorCode setFloat(uint c, float f);

		ErrorCode setVec2(uint c, const vec2& v);
		ErrorCode setVec3(uint c, const vec3& v);
		ErrorCode setVec4(uint c, const vec4& v);
		ErrorCode setMat3(uint c, const mat3& m);
		ErrorCode setMat4(uint c, const mat4& m);

		LPD3DXCONSTANTTABLE constants = 0;

	private:
		std::vector<D3DXHANDLE> handles;
	};

	~Shader();

	ErrorCode compile(const std::string& vert, const std::string& pixel);
	ErrorCode compileASM(const std::string& vert, const std::string& pixel);

	LPDIRECT3DVERTEXSHADER9 VShader = 0;
	LPDIRECT3DPIXELSHADER9  PShader = 0;

	ShaderConstants VConstants;
	ShaderConstants PConstants;
};
