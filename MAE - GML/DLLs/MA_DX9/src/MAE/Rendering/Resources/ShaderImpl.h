#pragma once

#include <MAE/Rendering/Resources/Shader.h>

#include <vector>
#include <d3dx9.h>

class ShaderImpl: public Shader
{
public:
	ShaderImpl(class MainImpl* main): main(main) { }
	~ShaderImpl();

	uint release();

	ErrorCode compile(const std::string& vert, const std::string& pixel, std::string& error);
	ErrorCode compileASM(const std::string& vert, const std::string& pixel, std::string& error);

	ErrorCode find(ShaderType type, const std::string& c, uint& ind);
	ErrorCode getSampler(ShaderType type, uint c, uint& ind);

	ErrorCode getVertexShader(LPDIRECT3DVERTEXSHADER9& vert);
	ErrorCode getPixelShader(LPDIRECT3DPIXELSHADER9& pixel);

	ErrorCode setFloat(ShaderType type, uint c, float f);
	ErrorCode setVec2(ShaderType type, uint c, const vec2& v);
	ErrorCode setVec3(ShaderType type, uint c, const vec3& v);
	ErrorCode setVec4(ShaderType type, uint c, const vec4& v);
	ErrorCode setMat3(ShaderType type, uint c, const mat3& m);
	ErrorCode setMat4(ShaderType type, uint c, const mat4& m);

private:
	class MainImpl* main;

	std::vector<D3DXHANDLE> handles;

	LPD3DXCONSTANTTABLE vtable = 0;
	LPD3DXCONSTANTTABLE ptable = 0;

	LPDIRECT3DVERTEXSHADER9 vshd = 0;
	LPDIRECT3DPIXELSHADER9  pshd = 0;
};

