#include <MAE/Rendering/Renderer.h>

#include <d3d9.h>

class RendererImpl: public Renderer {
public:
	RendererImpl(LPDIRECT3DDEVICE9 device): device(device) { }

	void release();

	class VertexBuffer* createVertexBuffer(uint length);
	class VertexData* createVertexData();
	void buildVertexData(class VertexData* vd);
	void setVertexData(class VertexData* vd);

	inline LPDIRECT3DDEVICE9 getDevice() {
		return device;
	}

private:
	LPDIRECT3DDEVICE9 device;
};
