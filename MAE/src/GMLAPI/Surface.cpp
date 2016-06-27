#include <MAE/Main.h>
#include <MAE/Core/Utils.h>
#include <MAE/Rendering/Resources/Surface.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

DLLEXPORT double MAE_SurfaceCreate()
{
	Surface* surf;
	ErrorCode ret;

	if ((ret = mamain->createSurface(surf)) != ErrorOk)
		return ret;

	return ptrToDouble(surf);
}

DLLEXPORT double MADX9_SurfaceCreateDepthStencil(double s, double width, double height, double format, double ms, double msquality, double discard)
{
	return doubleToPtr<Surface>(s)->createDepthStencil((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, discard >= 0.5);
}

DLLEXPORT double MADX9_SurfaceCreateFromPointer(double s, double ptr)
{
	return doubleToPtr<Surface>(s)->createFromPointer(doubleToPtr<IDirect3DSurface9>(ptr));
}

DLLEXPORT double MADX9_SurfaceCreateRenderTarget(double s, double width, double height, double format, double ms, double msquality, double lockable)
{
	return doubleToPtr<Surface>(s)->createRenderTarget((uint) width, (uint) height, (D3DFORMAT) (uint) format, (D3DMULTISAMPLE_TYPE) (uint) ms, (uint) msquality, lockable >= 0.5);
}

DLLEXPORT double MADX9_SurfaceDestroy(double s)
{
	delete doubleToPtr<Surface>(s);
	return ErrorOk;
}

DLLEXPORT double MADX9_SurfaceUpdate(double dest, double src)
{
	return doubleToPtr<Surface>(dest)->update(doubleToPtr<Surface>(src));
}

DLLEXPORT double MADX9_SurfaceGetPointer(double s)
{
	LPDIRECT3DSURFACE9 ptr;

	if (doubleToPtr<Surface>(s)->getSurf(ptr) != ErrorOk)
		return ptrToDouble<void>(nullptr);

	return ptrToDouble(ptr);
}
