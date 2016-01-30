#pragma once

#include "Surface.h"

class SurfaceImpl: public Surface
{
public:
	SurfaceImpl(class MainImpl* main): main(main) { };
	~SurfaceImpl();

	uint release();

	ErrorCode createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard);
	ErrorCode createFromPointer(LPDIRECT3DSURFACE9 surf);
	ErrorCode createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable);
	ErrorCode getPool(D3DPOOL& pool);
	ErrorCode getSurf(LPDIRECT3DSURFACE9& surf);
	ErrorCode update(Surface* surf);

private:
	class MainImpl* main;

	LPDIRECT3DSURFACE9 surf = 0;

	uint surfUsage;
	uint surfPool;
	uint surfWidth;
	uint surfHeight;
};
