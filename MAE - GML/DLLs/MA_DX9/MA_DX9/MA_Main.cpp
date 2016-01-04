#include "Main.h"
#include "Bullet.h"
#include "Navigation.h"
#include "Exception.h"

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	_GMEXBEG();

	mamain   = new MADX9Main(pointer);
	mabullet = new MABullet();
	manav    = new MANavigation();

	return 1;

	_GMEXENDSIMPLE(0);
}

DLLEXPORT double MADX9_Free()
{
	_GMEXBEG();

	if (mamain != 0) {
		delete mamain;
		delete mabullet;
		delete manav;
		mamain = 0;
	}

	return 1;

	_GMEXENDSIMPLE(0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		if (mamain != 0)
		{
			mamain->err.onError("MADX9 wasn't freed. MAE_Free() should be called at the end.");
			delete mamain;
			mamain = 0;
		}

		break;
	}

	return 1;
}
