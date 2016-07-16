#include <MAE/Main.h>
#include <MAE/Rendering/ModelMD2.h>
#include <MAE/Rendering/VertexBuffer.h>
#include <MAE/Rendering/ModelMPM.h>
#include <MAE/Rendering/ModelX.h>
#include <MAE/Rendering/ParticleSystem.h>
#include <MAE/MainImpl.h>
#include <MAE/Rendering/Resources/TextureImpl.h>
#include <MAE/Rendering/Resources/ShaderImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>
#include <MAE/Rendering/RendererImpl.h>

Main* mainObj = 0;

void MainImpl::release() {
	::delete this;
}

MainImpl::MainImpl(LPDIRECT3DDEVICE9 d3ddev) {
	d3ddev->AddRef();
	d3ddev->GetDirect3D(&d3d);
	d3d->AddRef();

	this->d3ddev = d3ddev;
}

MainImpl::~MainImpl() {
	assert(("Some MD2 Models weren't freed", MD2Models.size() == 0));
	assert(("Some MPM Models weren't freed", MPMModels.size() == 0));
	assert(("Some X Models weren't freed", XModels.size() == 0));
	assert(("Some Particel Systems weren't freed", ParticleSys.size() == 0));

	if (d3ddev != 0)
		d3ddev->Release();

	if (d3d != 0)
		d3d->Release();

	d3ddev = 0;
	d3d    = 0;
}

Renderer* MainImpl::createRendererDX9(LPDIRECT3DDEVICE9 device) {
	return ::new RendererImpl(device);
}

Main* MainCreate(LPDIRECT3DDEVICE9 device) {
	// return new(std::nothrow) MainImpl(device);
	return (mainObj = ::new(std::nothrow) MainImpl(device));
}
