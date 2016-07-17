#include <GMLAPI/Main.h>

#include <MAE/Main.h>
#include <MAE/Bullet/Bullet.h>
#include <MAE/Navigation/Navigation.h>
#include <MAE/Rendering/Renderer.h>

Main* mamain = 0;
Renderer* renderer = 0;

UnorderedVector<Stream*> streams;

void error(const char* msg) {
	MessageBox(nullptr, msg, "MAE", MB_OK | MB_ICONERROR);

	puts(msg);
	fflush(stdout);
}

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer) {
	mamain   = MainCreate();
	renderer = mamain->createRendererDX9(pointer);

	return 1;
}

DLLEXPORT double MADX9_Free() {
	if (renderer != nullptr) {
		delete renderer;
		renderer = nullptr;
	}
	
	if (mamain != nullptr) {
		delete mamain;
		mamain = nullptr;
	}

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_DETACH:
		assert(("MADX9 wasn't freed. MAE_Free() should be called at the end", mamain == nullptr));
		break;
	}

	return 1;
}
