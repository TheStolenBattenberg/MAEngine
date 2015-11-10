#include "Main.h"

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain.init(pointer);

	return 1;
}

DLLEXPORT double MADX9_Free()
{
	mamain.free();

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_DETACH:
		if (mamain.isInitialized())
			MessageBox(0, "MADX9 wasn't freed. MAE_Free() should be called at the end.", "MADX9", MB_OK | MB_ICONWARNING);

		break;
	}

	return 1;
}
