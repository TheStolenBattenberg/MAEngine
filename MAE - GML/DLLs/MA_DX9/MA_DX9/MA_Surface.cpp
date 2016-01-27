#include "Main.h"
#include "Utils.h"
#include "Surface.h"
#include "Texture.h"
#include "MA_Main.h"

DLLEXPORT double MAE_SurfaceCreate()
{
	Surface* surf;
	ErrorCode ret;

	if ((ret = mamain->createSurface(surf)) != ErrorOk)
		return ret;

	return VectorPushBackPointer(surf, surfaces);
}

DLLEXPORT double MADX9_SurfaceCreateDepthStencil(double index, double width, double height, double format, double ms, double msquality, double discard)
{
	Surface* surf = VectorGetPointerSafe((uint) index, surfaces);

	if (surf == 0)
		return mamain->setError(ErrorInv);

	return surf->createDepthStencil((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, discard >= 0.5);
}

DLLEXPORT double MADX9_SurfaceCreateFromPointer(double index, double ptr)
{
	Surface* surf = VectorGetPointerSafe((uint) index, surfaces);

	if (surf == 0)
		return mamain->setError(ErrorInv);

	return surf->createFromPointer((LPDIRECT3DSURFACE9) DoubleToPtr(ptr));
}

DLLEXPORT double MADX9_SurfaceCreateRenderTarget(double index, double width, double height, double format, double ms, double msquality, double lockable)
{
	Surface* surf = VectorGetPointerSafe((uint) index, surfaces);

	if (surf == 0)
		return mamain->setError(ErrorInv);

	return surf->createRenderTarget((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, lockable >= 0.5);
}

DLLEXPORT double MADX9_SurfaceDestroy(double index)
{
	Surface* surf = VectorGetPointerSafe((uint) index, surfaces);

	if (surf == 0)
		return mamain->setError(ErrorInv);

	surf->release();
	surfaces[(uint) index] = 0;

	return ErrorOk;
}

DLLEXPORT double MADX9_SurfaceUpdate(double dest, double src)
{
	Surface* destSurf = VectorGetPointerSafe((uint) dest, surfaces);
	Surface* srcSurf = VectorGetPointerSafe((uint) src, surfaces);

	if (destSurf == 0 || srcSurf == 0)
		return mamain->setError(ErrorInv);

	return destSurf->update(srcSurf);
}

DLLEXPORT double MADX9_SurfaceGetPointer(double index)
{
	Surface* surf = VectorGetPointerSafe((uint) index, surfaces);

	if (surf == 0)
		return PtrToDouble(0);

	LPDIRECT3DSURFACE9 ptr;

	if (surf->getSurf(ptr) != ErrorOk)
		return PtrToDouble(0);

	return PtrToDouble(ptr);
}
