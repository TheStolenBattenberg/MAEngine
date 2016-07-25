#include <MAE/Rendering/Renderer.h>

#include <d3d9.h>

class RendererImpl: public Renderer {
public:
	RendererImpl(LPDIRECT3DDEVICE9 device): device(device) { }

	~RendererImpl();

	void buildVertexData(class VertexData* vd);
	class IndexBuffer* createIndexBuffer(uint length, uint format);
	class Shader* createShader(const char* vshd, const char* pshd);
	class Texture* createTextureFromFile(const char* file, uint mipmaps);
	class Texture* createTextureFromFileInMemory(const void* data, uint length, uint mipmaps);
	class VertexBuffer* createVertexBuffer(uint length);
	class VertexData* createVertexData();
	class VertexData* copyVertexData(class VertexData* vd);
	void draw(class VertexData* vd, uint type, uint index, uint count);
	void drawIndexed(class VertexData* vd, uint type, uint count);
	void setShader(class Shader* shd);
	void setTexture(uint stage, class Texture* tex);

	inline LPDIRECT3DDEVICE9 getDevice() {
		return device;
	}

private:
	LPDIRECT3DDEVICE9 device;
};
