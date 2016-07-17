#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>
#include <string>

class Renderer: public Releasable {
public:
	enum {
		IndexBuffer16 = 0,
		IndexBuffer32 = 1
	};

	enum {
		MipMapsNone     = 0,
		MipMapsGenerate = 1,
		MipMapsFromFile = 2
	};

	enum {
		PrimitveTypePointList     = 0,
		PrimitveTypeLineList      = 1,
		PrimitveTypeLineStrip     = 2,
		PrimitveTypeTriangleList  = 3,
		PrimitveTypeTriangleStrip = 4,
		PrimitveTypeTriangleFan   = 5
	};

	inline class Shader* createShader(const std::string& vshd, const std::string& pshd) {
		return createShader(vshd.c_str(), pshd.c_str());
	}

	inline class Texture* createTextureFromFile(const std::string& file, uint mipmaps) {
		return createTextureFromFile(file.c_str(), mipmaps);
	}

	virtual void release() = 0;

	virtual class IndexBuffer* createIndexBuffer(uint length, uint format) = 0;
	virtual class Scene* createScene() = 0;
	virtual class Shader* createShader(const char* vshd, const char* pshd) = 0;
	virtual class Texture* createTextureFromFile(const char* file, uint mipmaps) = 0;
	virtual class Texture* createTextureFromFileInMemory(const void* data, uint length, uint mipmaps) = 0;
	virtual class VertexBuffer* createVertexBuffer(uint length) = 0;
	virtual class VertexData* createVertexData(class VertexDataBuilder* vdb) = 0;
	virtual class VertexDataBuilder* createVertexDataBuilder() = 0;
	virtual void draw(uint type, uint index, uint count) = 0;
	virtual void drawIndexed(uint type, uint count) = 0;
	virtual void setShader(class Shader* shd) = 0;
	virtual void setTexture(uint stage, class Texture* tex) = 0;
	virtual void setVertexData(class VertexData* vd) = 0;
};
