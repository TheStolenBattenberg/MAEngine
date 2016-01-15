#include "Surface.h"
#include "Utils.h"

const uint MaxRenderTargets = 16;

std::stack<LPDIRECT3DSURFACE9> DepthBuffers;
std::stack<LPDIRECT3DSURFACE9> RenderTargets[MaxRenderTargets];
std::stack<D3DVIEWPORT9>       Viewports[MaxRenderTargets];

Surface::~Surface()
{
	if (surf != 0)
		surf->Release();
}

ErrorCode Surface::createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard)
{
	if (surf != 0)
	{
		surf->Release();
		surf = 0;
	}

	HRESULT res = mamain->d3ddev->CreateDepthStencilSurface(width, height, format, ms, msquality, discard, &surf, 0);

	if (FAILED(res))
		return ErrorHandleCritical(mamain->err, mamain->errCrit, ErrorD3D9, res, "CreateDepthStencilSurface");

	surfUsage = D3DUSAGE_DEPTHSTENCIL;
	surfPool = D3DPOOL_DEFAULT;
	surfWidth = width;
	surfHeight = height;

	return ErrorOk;
}

ErrorCode Surface::createFromPointer(LPDIRECT3DSURFACE9 surf)
{
	if (this->surf != 0)
	{
		this->surf->Release();
		this->surf = 0;
	}

	if (surf == 0)
		return ErrorHandle(mamain->err, ErrorInv);

	D3DSURFACE_DESC desc;

	HRESULT res = surf->GetDesc(&desc);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "GetDesc");

	surfUsage = desc.Usage;
	surfPool = desc.Pool;
	surfWidth = desc.Width;
	surfHeight = desc.Height;

	this->surf = surf;
	surf->AddRef();

	return ErrorOk;
}

ErrorCode Surface::createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable)
{
	if (surf != 0)
	{
		surf->Release();
		surf = 0;
	}

	HRESULT res = mamain->d3ddev->CreateRenderTarget(width, height, format, ms, msquality, lockable, &surf, 0);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "CreateRenderTarget");

	surfUsage = D3DUSAGE_RENDERTARGET;
	surfPool = D3DPOOL_DEFAULT;
	surfWidth = width;
	surfHeight = height;

	return ErrorOk;
}

ErrorCode Surface::setRenderTarget(uint level)
{
	if ((surfUsage & D3DUSAGE_RENDERTARGET) == 0 || level > MaxRenderTargets)
		return ErrorHandle(mamain->err, ErrorInv);

	LPDIRECT3DSURFACE9 surf;

	HRESULT res = mamain->d3ddev->GetRenderTarget(level, &surf);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "GetRenderTarget");

	D3DVIEWPORT9 vp;

	mamain->d3ddev->GetViewport(&vp);

	Viewports[level].push(vp);

	RenderTargets[level].push(surf);

	vp.X = 0;
	vp.Y = 0;
	vp.Width = surfWidth;
	vp.Height = surfHeight;
	vp.MinZ = 0;
	vp.MaxZ = 1;

	res = mamain->d3ddev->SetRenderTarget(level, this->surf);

	mamain->d3ddev->SetViewport(&vp);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetRenderTarget");

	return ErrorOk;
}

ErrorCode Surface::resetRenderTarget(uint level)
{
	if (level > MaxRenderTargets || RenderTargets[level].empty())
		return ErrorHandle(mamain->err, ErrorInv);

	LPDIRECT3DSURFACE9 surf = RenderTargets[level].top();

	RenderTargets[level].pop();

	surf->Release();

	HRESULT res = mamain->d3ddev->SetRenderTarget(level, surf);

	mamain->d3ddev->SetViewport(&Viewports[level].top());
	Viewports[level].pop();

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetRenderTarget");

	return ErrorOk;
}

ErrorCode Surface::setDepthBuffer()
{
	if ((surfUsage & D3DUSAGE_DEPTHSTENCIL) == 0)
		return ErrorHandle(mamain->err, ErrorInv);

	LPDIRECT3DSURFACE9 surf;

	HRESULT res = mamain->d3ddev->GetDepthStencilSurface(&surf);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "GetDepthStencilSurface");

	DepthBuffers.push(surf);

	res = mamain->d3ddev->SetDepthStencilSurface(this->surf);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetDepthStencilSurface");

	return ErrorOk;
}

ErrorCode Surface::resetDepthBuffer()
{
	if (DepthBuffers.empty())
		return ErrorHandle(mamain->err, ErrorInv);

	LPDIRECT3DSURFACE9 surf = DepthBuffers.top();

	DepthBuffers.pop();

	surf->Release();

	HRESULT res = mamain->d3ddev->SetDepthStencilSurface(surf);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetDepthStencilSurface");

	return ErrorOk;
}

ErrorCode Surface::update(Surface& surf)
{
	if (surfPool == D3DPOOL_DEFAULT && surf.surfPool == D3DPOOL_DEFAULT)
		return ErrorHandle(mamain->err, ErrorInv);

	HRESULT res;

	if (surfPool == D3DPOOL_DEFAULT)
		res = mamain->d3ddev->UpdateSurface(surf.surf, 0, this->surf, 0);
	else
		res = mamain->d3ddev->GetRenderTargetData(surf.surf, this->surf);

	if (FAILED(res))
		return ErrorHandle(mamain->err, ErrorD3D9, res, "SetDepthStencilSurface");

	return ErrorOk;
}
