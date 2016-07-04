#include <MAE/Main.h>
#include <MAE/Bullet/Bullet.h>
#include <MAE/Navigation/Navigation.h>
#include <GMLAPI/Main.h>

Main* mamain = 0;

UnorderedVector<Stream*> streams;

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain   = MainCreate(pointer);
	return 1;
}

DLLEXPORT double MADX9_Free()
{
	if (mamain != 0) {
		mamain->release();
		mamain = 0;
	}

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		assert(("MADX9 wasn't freed. MAE_Free() should be called at the end", mamain == 0));
		break;
	}

	return 1;
}
