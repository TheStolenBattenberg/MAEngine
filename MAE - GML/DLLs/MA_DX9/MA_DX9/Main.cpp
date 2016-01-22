#include "Main.h"
#include "Hook.h"
#include "ModelMD2.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexDecl.h"
#include "Utils.h"
#include "ModelMPM.h"
#include "ModelX.h"
#include "ParticleSystem.h"
#include "MainImpl.h"
#include "SurfaceImpl.h"
#include "TextureImpl.h"
#include "ShaderImpl.h"

uint MainImpl::release()
{
	if (--count == 0)
		delete this;

	return count;
}

MainImpl::MainImpl(LPDIRECT3DDEVICE9 d3ddev)
{
	d3ddev->AddRef();
	d3ddev->GetDirect3D(&d3d);
	d3d->AddRef();

	this->d3ddev = d3ddev;

	hook = new Hook(d3ddev);
}

MainImpl::~MainImpl()
{
	ClearVector(MD2Models);
	ClearVector(MPMModels);
	ClearVector(Light);
	ClearVector(Material);
	ClearVector(Buffers);
	ClearVector(VertexDeclarations);
	ClearVector(VertexBuffers);
	ClearVector(XModels);
	ClearVector(ParticleSys);

	for (auto i : shaders)
		delete i;

	for (auto i : surfaces)
		delete i;

	for (auto i : textures)
		delete i;

	if (VertexDeclarationParticle != 0)
	{
		VertexDeclarationParticle->Release();
		VertexDeclarationParticle = 0;
	}

	if (d3ddev != 0)
		d3ddev->Release();

	if (d3d != 0)
		d3d->Release();

	d3ddev = 0;
	d3d    = 0;

	delete hook;

	hook  = 0;
}

ErrorCode MainImpl::setError(ErrorCode code)
{
	return errCode = code;
}

ErrorCode MainImpl::getError()
{
	return errCode;
}

ErrorCode MainImpl::surfaceCreate(Surface*& surf)
{
	SurfaceImpl* s = new(std::nothrow) SurfaceImpl(this);

	if (s == 0)
		return this->setError(ErrorMemory);

	surfaces.push_back(s);
	surf = s;

	return ErrorOk;
}

ErrorCode MainImpl::surfaceExists(const Surface* surf, bool& exists)
{
	exists = 0;

	if (surf != 0)
	{
		if (std::find(surfaces.begin(), surfaces.end(), (SurfaceImpl*) surf) != surfaces.end())
			exists = 1;
	}

	return ErrorOk;
}

void MainImpl::surfaceRemove(const Surface* surf)
{
	surfaces.remove_if([surf](Surface* s) {
		return s == surf;
	});
}

ErrorCode MainImpl::textureCreate(Texture*& tex)
{
	TextureImpl* t = new(std::nothrow) TextureImpl(this);

	if (t == 0)
		return this->setError(ErrorMemory);

	textures.push_back(t);
	tex = t;

	return ErrorOk;
}

ErrorCode MainImpl::textureExists(const Texture* tex, bool& exists)
{
	exists = 0;

	if (tex != 0)
	{
		if (std::find(textures.begin(), textures.end(), (TextureImpl*) tex) != textures.end())
			exists = 1;
	}

	return ErrorOk;
}

void MainImpl::textureRemove(const Texture* tex)
{
	textures.remove_if([tex](Texture* t) {
		return t == tex;
	});
}

ErrorCode MainImpl::shaderCreate(Shader*& shd)
{
	ShaderImpl* s = new(std::nothrow) ShaderImpl(this);

	if (s == 0)
		return setError(ErrorMemory);

	shaders.push_back(s);
	shd = s;

	return ErrorOk;
}

ErrorCode MainImpl::shaderExists(const Shader* shd, bool& exists)
{
	exists = 0;

	if (shd != 0)
	{
		if (std::find(shaders.begin(), shaders.end(), (ShaderImpl*) shd) != shaders.end())
			exists = 1;
	}

	return ErrorOk;
}

void MainImpl::shaderRemove(const Shader* shd)
{
	shaders.remove_if([shd](Shader* s) {
		return s == shd;
	});
}

ErrorCode MainImpl::setTexture(uint stage, class Texture* tex)
{
	LPDIRECT3DTEXTURE9 t;

	ErrorCode ret = tex->getTexture(t);

	if (ret != ErrorOk)
		return ret;
	
	HRESULT res = d3ddev->SetTexture(stage, t);

	t->Release();

	if (FAILED(res))
		return setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode MainImpl::resetTexture(uint stage)
{
	if (FAILED(d3ddev->SetTexture(stage, 0)))
		return setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode MainImpl::setShader(Shader* shd)
{
	LPDIRECT3DVERTEXSHADER9 vshd;
	LPDIRECT3DPIXELSHADER9 pshd;

	ErrorCode ret;
	
	if ((ret = shd->getVertexShader(vshd)) != ErrorOk)
		return ret;

	if ((ret = shd->getPixelShader(pshd)) != ErrorOk)
	{
		vshd->Release();
		return ret;
	}

	d3ddev->SetVertexShader(vshd);
	d3ddev->SetPixelShader(pshd);

	vshd->Release();
	pshd->Release();

	return ErrorOk;
}

ErrorCode MainImpl::resetShader()
{
	d3ddev->SetVertexShader(0);
	d3ddev->SetPixelShader(0);

	return ErrorOk;
}

Main* MainCreate(LPDIRECT3DDEVICE9 device)
{
	return new(std::nothrow) MainImpl(device);
}
