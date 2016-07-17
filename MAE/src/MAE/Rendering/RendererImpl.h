#include <MAE/Rendering/Renderer.h>

#include <d3d9.h>

class RendererImpl: public Renderer {
public:
	RendererImpl(LPDIRECT3DDEVICE9 device): device(device) { }

	void release();

	void buildVertexData(class VertexData* vd);
	class IndexBuffer* createIndexBuffer(uint length, uint format);
	class Scene* createScene();
	class Shader* createShader(const char* vshd, const char* pshd);
	class Texture* createTextureFromFile(const char* file, MipMaps mipmaps);
	class Texture* createTextureFromFileInMemory(const void* data, uint length, MipMaps mipmaps);
	class VertexBuffer* createVertexBuffer(uint length);
	class VertexData* createVertexData();
	void draw(uint type, uint index, uint count);
	void drawIndexed(uint type, uint count);
	void setIndexBuffer(class IndexBuffer* ib);
	void setShader(class Shader* shd);
	void setTexture(uint stage, class Texture* tex);
	void setVertexData(class VertexData* vd);

	inline LPDIRECT3DDEVICE9 getDevice() {
		return device;
	}

private:
	LPDIRECT3DDEVICE9 device;

	class VertexDataImpl* vd = 0;
};
