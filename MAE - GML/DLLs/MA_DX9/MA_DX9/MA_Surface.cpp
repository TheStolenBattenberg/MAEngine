#include "Main.h"
#include "Utils.h"
#include "Surface.h"
#include "Texture.h"

DLLEXPORT double MADX9_SurfaceCreateDepthStencil(double width, double height, double format, double ms, double msquality, double discard)
{
	Surface* surf = new Surface();

	ErrorCode ret = surf->createDepthStencil((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, discard ? 1 : 0);
	
	if (ret != ErrorOk)
	{
		delete surf;
		return ret;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateFromPointer(double ptr)
{
	Surface* surf = new Surface();

	ErrorCode ret = surf->createFromPointer(*(LPDIRECT3DSURFACE9*) &ptr);

	if (ret != ErrorOk)
	{
		delete surf;
		return ret;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateFromTexture(double tex, double level)
{
	if (!isValidIndex((uint) tex, mamain->Textures))
		return -1;
	
	Surface* surf = new Surface();

	ErrorCode ret = mamain->Textures[(uint) tex]->getSurface((uint) level, *surf);
	
	if (ret != ErrorOk)
	{
		delete surf;
		return ret;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateRenderTarget(double width, double height, double format, double ms, double msquality, double lockable)
{
	Surface* surf = new Surface();

	ErrorCode ret = surf->createRenderTarget((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, lockable ? 1 : 0);

	if (ret != ErrorOk)
	{
		delete surf;
		return ret;
	}

	return putInto(surf, mamain->Surfaces);
}

DLLEXPORT double MADX9_SurfaceDestroy(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return ErrorHandle(mamain->err, ErrorInv);

	delete mamain->Surfaces[(uint) ind];
	mamain->Surfaces[(uint) ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_SurfaceSetRenderTarget(double ind, double level)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return ErrorHandle(mamain->err, ErrorInv);

	return mamain->Surfaces[(uint) ind]->setRenderTarget((uint) level);
}

DLLEXPORT double MADX9_SurfaceResetRenderTarget(double level)
{
	return Surface::resetRenderTarget((uint) level);
}

DLLEXPORT double MADX9_SurfaceSetDepthBuffer(double ind)
{
	if (!isValidIndex((uint) ind, mamain->Surfaces))
		return ErrorHandle(mamain->err, ErrorInv);

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
		return ErrorHandle(mamain->err, ErrorInv);

	return mamain->Surfaces[(uint) dest]->update(*mamain->Surfaces[(uint) src]);
}

DLLEXPORT double MADX9_SurfaceGetPointer(double ind)
{
	if (isValidIndex((uint) ind, mamain->Surfaces))
		return 0;

	mamain->Surfaces[(uint) ind]->surf->AddRef();
	return PtrToDouble(mamain->Surfaces[(uint) ind]->surf);
}
