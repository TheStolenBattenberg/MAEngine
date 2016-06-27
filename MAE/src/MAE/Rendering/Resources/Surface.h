#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/Releasable.h>

#include <d3d9.h>

class Surface: public Releasable
{
public:
	virtual void release() = 0;

	virtual ErrorCode createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard) = 0;
	virtual ErrorCode createFromPointer(LPDIRECT3DSURFACE9 surf) = 0;
	virtual ErrorCode createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable) = 0;
	
	virtual ErrorCode getSurf(LPDIRECT3DSURFACE9& surf) = 0;
	virtual ErrorCode getPool(D3DPOOL& pool) = 0;

	virtual ErrorCode update(Surface* surf) = 0;
};
