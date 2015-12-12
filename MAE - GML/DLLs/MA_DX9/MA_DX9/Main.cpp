#include "Main.h"
#include "Hook.h"
#include "Resources.h"
#include "ModelMD2.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexDecl.h"
#include "Utils.h"

MADX9Main* mamain = 0;

MADX9Main::MADX9Main(LPDIRECT3DDEVICE9 d3ddev)
{
	err.flags = Error::ShowMessage | Error::ShowDebugMessage;

	d3ddev->AddRef();
	d3ddev->GetDirect3D(&d3d);
	d3d->AddRef();

	this->d3ddev = d3ddev;

	hook = new Hook(d3ddev);
}

MADX9Main::~MADX9Main()
{
	ClearVector(Shader);
	ClearVector(MD2Models);
	ClearVector(Surfaces);
	ClearVector(Textures);
	ClearVector(Light);
	ClearVector(Material);
	ClearVector(Buffers);
	ClearVector(VertexDeclarations);
	ClearVector(VertexBuffers);

	if (VertexDeclarationMPM != 0)
	{
		VertexDeclarationMPM->Release();
		VertexDeclarationMPM = 0;
	}

	if (d3ddev != 0)
		d3ddev->Release();

	if (d3d != 0)
		d3d->Release();

	d3ddev = 0;
	d3d    = 0;

	delete hook;

	hook  = 0;
}

const char* MADX9Main::returnStr(std::string& str)
{
	return (retStr = str).c_str();
}

DLLEXPORT double MADX9_Init(LPDIRECT3DDEVICE9 pointer)
{
	mamain = new MADX9Main(pointer);

	return 1;
}

DLLEXPORT double MADX9_Free()
{
	if (mamain != 0)
		delete mamain;

	mamain = 0;

	return 1;
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
