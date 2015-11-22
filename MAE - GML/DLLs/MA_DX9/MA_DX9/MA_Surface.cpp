#include "Main.h"
#include "Utils.h"

DLLEXPORT double MADX9_SurfaceCreateDepthStencil(double width, double height, double format, double ms, double msquality, double discard)
{
	Surface* surf = new Surface();

	if (!surf->createDepthStencil((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, discard ? 1 : 0))
	{
		delete surf;
		return -1;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateFromPointer(double ptr)
{
	Surface* surf = new Surface();

	if (!surf->createFromPointer(*(LPDIRECT3DSURFACE9*) &ptr))
	{
		delete surf;
		return -1;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateFromTexture(double tex, double level)
{
	if (!isValidIndex((uint) tex, mamain->Textures))
		return -1;
	
	Surface* surf = new Surface();

	if (!mamain->Textures[(uint) tex]->getSurface((uint) level, *surf))
	{
		delete surf;
		return -1;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateRenderTarget(double width, double height, double format, double ms, double msquality, double lockable)
{
	Surface* surf = new Surface();

	if (!surf->createRenderTarget((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, lockable ? 1 : 0))
	{
		delete surf;
		return -1;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return 0;

	delete mamain->Surfaces[(uint) ind];
	mamain->Surfaces[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_SurfaceSetRenderTarget(double ind, double level)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return 0;

	return mamain->Surfaces[(uint) ind]->setRenderTarget((uint) level);
}

DLLEXPORT double MADX9_SurfaceResetRenderTarget(double level)
{
	return Surface::resetRenderTarget((uint) level);
}

DLLEXPORT double MADX9_SurfaceSetDepthBuffer(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return 0;

	return mamain->Surfaces[(uint) ind]->setDepthBuffer();
}

DLLEXPORT double MADX9_SurfaceResetDepthBuffer()
{
	return Surface::resetDepthBuffer();
}

DLLEXPORT double MADX9_SurfaceUpdate(double dest, double src)
{
	if (!isValidIndex((uint) dest, mamain->Surfaces) ||
	    !isValidIndex((uint) src, mamain->Surfaces))
		return 0;

	return mamain->Surfaces[(uint) dest]->update(*mamain->Surfaces[(uint) src]);
}

DLLEXPORT double MADX9_SurfaceGetPointer(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return -1;

	double ret = 0;

	*(LPDIRECT3DSURFACE9*) &ret = mamain->Surfaces[(uint) ind]->surf;

	return ret;
}
