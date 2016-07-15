#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>
#include <string>

class Renderer: public Releasable {
public:
	enum MipMaps {
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	inline class Shader* createShader(const std::string& vshd, const std::string& pshd) {
		return createShader(vshd.c_str(), pshd.c_str());
	}

	inline class Texture* createTextureFromFile(const std::string& file, MipMaps mipmaps) {
		return createTextureFromFile(file.c_str(), mipmaps);
	}

	virtual void release() = 0;

	virtual void buildVertexData(class VertexData* vd) = 0;
	virtual class Scene* createScene() = 0;
	virtual class Shader* createShader(const char* vshd, const char* pshd) = 0;
	virtual class Texture* createTextureFromFile(const char* file, MipMaps mipmaps) = 0;
	virtual class Texture* createTextureFromFileInMemory(const void* data, uint length, MipMaps mipmaps) = 0;
	virtual class VertexBuffer* createVertexBuffer(uint length) = 0;
	virtual class VertexData* createVertexData() = 0;
	virtual void setShader(class Shader* shd) = 0;
	virtual void setTexture(uint stage, class Texture* tex) = 0;
	virtual void setVertexData(class VertexData* vd) = 0;
};
