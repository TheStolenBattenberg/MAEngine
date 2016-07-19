#include <MAE/MainImpl.h>
#include <MAE/Rendering/RendererImpl.h>

MainImpl::~MainImpl() {
	assert(("Some MD2 Models weren't freed", MD2Models.size() == 0));
	assert(("Some MPM Models weren't freed", MPMModels.size() == 0));
	assert(("Some X Models weren't freed", XModels.size() == 0));
	assert(("Some Particel Systems weren't freed", ParticleSys.size() == 0));
}

Renderer* MainImpl::createRendererDX9(LPDIRECT3DDEVICE9 device) {
	return new RendererImpl(device);
}

Main* MainCreate() {
	return new MainImpl();
}
