#pragma once

#include <MAE/Rendering/Resources/Shader.h>

#include <vector>
#include <d3dx9.h>

class ShaderImpl: public Shader {
public:
	ShaderImpl(class RendererImpl* device, const char* vshd, const char* pshd);
	~ShaderImpl();

	uint find(const char* c);
	void setSampler(uint c, class Texture* sampler);
	uint getLocation(const char* str);
	void setFloat(uint c, float f);
	void setVec2(uint c, const vec2& v);
	void setVec3(uint c, const vec3& v);
	void setVec4(uint c, const vec4& v);
	void setMat3(uint c, const mat3& m);
	void setMat4(uint c, const mat4& m);

	inline LPDIRECT3DVERTEXSHADER9 getVertexShader() {
		return vshd;
	}

	inline LPDIRECT3DPIXELSHADER9 getPixelShader() {
		return pshd;
	}

private:
	struct Handles {
		D3DXHANDLE vshd;
		D3DXHANDLE pshd;

		bool operator==(const Handles& a) const {
			return vshd == a.vshd && pshd == a.pshd;
		}
	};

	std::vector<Handles> handles;

	class RendererImpl* renderer;

	LPD3DXCONSTANTTABLE vtable = 0;
	LPD3DXCONSTANTTABLE ptable = 0;

	LPDIRECT3DVERTEXSHADER9 vshd = 0;
	LPDIRECT3DPIXELSHADER9  pshd = 0;
};
