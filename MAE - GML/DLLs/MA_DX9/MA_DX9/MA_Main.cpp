#include "Main.h"
#include "Bullet.h"
#include "Navigation.h"

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain   = new MADX9Main(pointer);
	mabullet = new MABullet();
	manav    = new MANavigation();

	return 1;
}

DLLEXPORT double MADX9_Free()
{
	if (mamain != 0) {
		delete mamain;
		delete mabullet;
		delete manav;
		mamain = 0;
	}

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		if (mamain != 0)
		{
			MessageBox(0, "MADX9 wasn't freed. MAE_Free() should be called at the end.", "MAE", MB_OK | MB_ICONERROR);

			delete mamain;
			mamain = 0;
		}
		break;
	}

	return 1;
}
