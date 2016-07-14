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

MainImpl::MainImpl(LPDIRECT3DDEVICE9 d3ddev)
{
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
	assert(("Some Shaders weren't freed", shaders.size() == 0));
	assert(("Some Texture weren't freed", textures.size() == 0));

	if (VertexDeclarationParticle != 0) {
		VertexDeclarationParticle->Release();
		VertexDeclarationParticle = 0;
	}

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

Scene* MainImpl::createScene() {
	auto s = ::new SceneImpl(this);
	scenes.add(s);
	return s;
}

Texture* MainImpl::createTexture() {
	auto t = ::new TextureImpl(this);
	textures.add(t);
	return t;
}

void MainImpl::removeTexture(const Texture* tex) {
	textures.remove((TextureImpl*) tex);
}

Shader* MainImpl::createShader() {
	auto s = ::new ShaderImpl(this);
	shaders.add(s);
	return s;
}

void MainImpl::removeShader(const Shader* shd) {
	shaders.remove((ShaderImpl*) shd);
}

void MainImpl::setTexture(uint stage, class Texture* tex) {
	if (FAILED(d3ddev->SetTexture(stage, tex != nullptr ? ((TextureImpl*) tex)->getTexture() : nullptr)))
		throw new std::exception("Failed to set texture");
}

void MainImpl::setShader(Shader* shd) {
	if (shd == nullptr) {
		d3ddev->SetVertexShader(nullptr);
		d3ddev->SetPixelShader(nullptr);
	}
	else {
		d3ddev->SetVertexShader(((ShaderImpl*) shd)->getVertexShader());
		d3ddev->SetPixelShader(((ShaderImpl*) shd)->getPixelShader());
	}
}

void MainImpl::removeScene(const class Scene* scene) {
	scenes.remove((SceneImpl*) scene);
}

Main* MainCreate(LPDIRECT3DDEVICE9 device)
{
	// return new(std::nothrow) MainImpl(device);
	return (mainObj = ::new(std::nothrow) MainImpl(device));
}
