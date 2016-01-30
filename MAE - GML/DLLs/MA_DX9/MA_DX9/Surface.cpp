#include "SurfaceImpl.h"
#include "Utils.h"
#include "MainImpl.h"

#include <list>

uint SurfaceImpl::release()
{
	if (--count == 0)
		delete this;

	return count;
}

SurfaceImpl::~SurfaceImpl()
{
	main->removeSurface(this);

	if (surf != 0)
		surf->Release();
}

ErrorCode SurfaceImpl::createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard)
{
	if (surf != 0)
	{
		surf->Release();
		surf = 0;
	}

	HRESULT res = main->d3ddev->CreateDepthStencilSurface(width, height, format, ms, msquality, discard, &surf, 0);

	if (FAILED(res))
		return main->setError(ErrorCreateSurface);

	surfUsage  = D3DUSAGE_DEPTHSTENCIL;
	surfPool   = D3DPOOL_DEFAULT;
	surfWidth  = width;
	surfHeight = height;

	return ErrorOk;
}

ErrorCode SurfaceImpl::createFromPointer(LPDIRECT3DSURFACE9 surf)
{
	if (this->surf != 0)
	{
		this->surf->Release();
		this->surf = 0;
	}

	if (surf == 0)
		return main->setError(ErrorInv);

	D3DSURFACE_DESC desc;

	HRESULT res = surf->GetDesc(&desc);

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	surfUsage  = desc.Usage;
	surfPool   = desc.Pool;
	surfWidth  = desc.Width;
	surfHeight = desc.Height;

	this->surf = surf;
	surf->AddRef();

	return ErrorOk;
}

ErrorCode SurfaceImpl::createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable)
{
	if (surf != 0)
	{
		surf->Release();
		surf = 0;
	}

	HRESULT res = main->d3ddev->CreateRenderTarget(width, height, format, ms, msquality, lockable, &surf, 0);

	if (FAILED(res))
		return main->setError(ErrorCreateSurface);

	surfUsage = D3DUSAGE_RENDERTARGET;
	surfPool = D3DPOOL_DEFAULT;
	surfWidth = width;
	surfHeight = height;

	return ErrorOk;
}

ErrorCode SurfaceImpl::update(Surface* surf)
{
	D3DPOOL pool;

	ErrorCode ret = surf->getPool(pool);

	if (ret != ErrorOk)
		return ret;

	if (surfPool == D3DPOOL_DEFAULT && pool == D3DPOOL_DEFAULT)
		return main->setError(ErrorInv);

	LPDIRECT3DSURFACE9 s;

	if ((ret = surf->getSurf(s)) != ErrorOk)
		return ret;

	HRESULT res;

	if (surfPool == D3DPOOL_DEFAULT)
		res = main->d3ddev->UpdateSurface(s, 0, this->surf, 0);
	else
		res = main->d3ddev->GetRenderTargetData(s, this->surf);

	s->Release();

	if (FAILED(res))
		return main->setError(ErrorD3D9);

	return ErrorOk;
}

ErrorCode SurfaceImpl::getSurf(LPDIRECT3DSURFACE9& surf)
{
	if (this->surf == 0)
		return main->setError(ErrorInv);

	this->surf->AddRef();
	surf = this->surf;

	return ErrorOk;
}

ErrorCode SurfaceImpl::getPool(D3DPOOL& pool)
{
	if (surf == 0)
		return main->setError(ErrorInv);

	pool = (D3DPOOL) surfPool;

	return ErrorOk;
}
