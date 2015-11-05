#include "Main.h"

MADLLMain mamain;

MADLLMain::MADLLMain()
{
	err.flags = ErrorShowMessage | ErrorShowDebugMessage;
}

void MADLLMain::init(LPDIRECT3DDEVICE9 d3ddev)
{
	if ((flags & FlagInitialized) == 0)
	{
		d3ddev->AddRef();
		d3ddev->GetDirect3D(&d3d);

		this->d3ddev = d3ddev;

		flags |= FlagInitialized;
	}
}

void MADLLMain::free()
{
	flags &= ~FlagInitialized;

	for (uint i = 0; i < mamain.Shader.size(); ++i)
		if (mamain.Shader[i] != 0)
			delete mamain.Shader[i];

	mamain.Shader.clear();

	for (uint i = 0; i < mamain.MD2Models.size(); ++i)
		if (mamain.MD2Models[i] != 0)
			delete mamain.MD2Models[i];

	mamain.MD2Models.clear();

	if (mamain.VertexDeclarationMD2 != 0) {
		mamain.VertexDeclarationMD2->Release();
		mamain.VertexDeclarationMD2 = 0;
	}

	for (uint i = 0; i < mamain.Hooks.size(); ++i)
		if (mamain.Hooks[i] != 0)
			delete mamain.Hooks[i];

	mamain.Hooks.clear();

	if (d3ddev != 0)
		d3ddev->Release();

	if (d3ddev != 0)
		d3d->Release();

	d3ddev = 0;
	d3d    = 0;
}

const char* MADLLMain::returnStr(std::string str)
{
	return (retStr = str).c_str();
}

void MADLLMain::reset()
{
	// TODO: Add code to handle resets
}

bool MADLLMain::isInitialized()
{
	return flags & FlagInitialized;
}
