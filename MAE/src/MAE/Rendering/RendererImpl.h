#include <MAE/Rendering/Renderer.h>

#include <d3d9.h>

class RendererImpl: public Renderer {
public:
	RendererImpl(LPDIRECT3DDEVICE9 device): device(device) { }

	void release();

	class VertexBuffer* createVertexBuffer(uint length);

	inline LPDIRECT3DDEVICE9 getDevice() {
		return device;
	}

private:
	LPDIRECT3DDEVICE9 device;
};
