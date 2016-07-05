#pragma once

#include <MAE/Core/Types.h>

#include <string>
#include <Mat.h>
#include <Vec.h>

#include <MAE/Core/Releasable.h>

class Shader: public Releasable {
public:
	virtual void release() = 0;

	virtual void compileD3D9(const std::string& vert, const std::string& pixel) = 0;
	virtual void compileD3D9ASM(const std::string& vert, const std::string& pixel) = 0;

	virtual uint find(const std::string& c) = 0;
	virtual void setSampler(uint c, class Texture* sampler) = 0;

	virtual void setFloat(uint c, float f) = 0;
	virtual void setVec2(uint c, const vec2& v) = 0;
	virtual void setVec3(uint c, const vec3& v) = 0;
	virtual void setVec4(uint c, const vec4& v) = 0;
	virtual void setMat3(uint c, const mat3& m) = 0;
	virtual void setMat4(uint c, const mat4& m) = 0;
};
