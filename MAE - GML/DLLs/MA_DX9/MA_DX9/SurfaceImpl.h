#pragma once

#include "Surface.h"
#include "MainImpl.h"

class SurfaceImpl: public Surface
{
public:
	SurfaceImpl(MainImpl* main);
	~SurfaceImpl();

	uint release();

	ErrorCode createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard);
	ErrorCode createFromPointer(LPDIRECT3DSURFACE9 surf);
	ErrorCode createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable);

	ErrorCode getSurf(LPDIRECT3DSURFACE9& surf);
	ErrorCode getPool(D3DPOOL& pool);

	ErrorCode update(Surface* surf);

protected:
	MainImpl* main;

	LPDIRECT3DSURFACE9 surf = 0;

	uint surfUsage;
	uint surfPool;
	uint surfWidth;
	uint surfHeight;
};
