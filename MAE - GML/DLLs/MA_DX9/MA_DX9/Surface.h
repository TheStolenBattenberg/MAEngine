#pragma once

#include "Main.h"

class Surface
{
public:
	~Surface();

	ErrorCode createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard);
	ErrorCode createFromPointer(LPDIRECT3DSURFACE9 surf);
	ErrorCode createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable);

	ErrorCode setRenderTarget(uint level);
	static ErrorCode resetRenderTarget(uint level);

	ErrorCode setDepthBuffer();
	static ErrorCode resetDepthBuffer();

	ErrorCode update(Surface& surf);

	LPDIRECT3DSURFACE9 surf;

protected:
	uint surfUsage;
	uint surfPool;
	uint surfWidth;
	uint surfHeight;
};
