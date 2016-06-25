#include <MAE/Main.h>
#include <MAE/Bullet/Bullet.h>
#include <MAE/Navigation/Navigation.h>
#include <GMLAPI/Main.h>

Main* mamain = 0;

std::vector<Surface*> surfaces;
std::vector<Texture*> textures;
std::vector<Shader*>  shaders;

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain   = MainCreate(pointer);
	mabullet = new MABullet();
	manav    = new MANavigation();

	return 1;
}

DLLEXPORT double MADX9_Free()
{
	if (mamain != 0) {
		mamain->release();
		mamain = 0;

		delete mabullet;
		delete manav;
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

			mamain->release();
			mamain = 0;
		}
		break;
	}

	return 1;
}
