#include "Main.h"

MADLLMain mamain;

MADLLMain::MADLLMain()
{
	err.flags = ErrorShowMessage | ErrorShowDebugMessage;
}

void MADLLMain::init(LPDIRECT3DDEVICE9 d3ddev)
{
	if (!isInitialized())
	{
		d3ddev->AddRef();
		d3ddev->GetDirect3D(&d3d);

		this->d3ddev = d3ddev;

		hook = new D3DHook(d3ddev);
		flush = new Flush();

		flags |= FlagInitialized;
	}
}

void MADLLMain::free()
{
	flags &= ~FlagInitialized;

	for (uint i = 0; i < Shader.size(); ++i)
		if (Shader[i] != 0)
			delete Shader[i];

	Shader.clear();

	for (uint i = 0; i < MD2Models.size(); ++i)
		if (MD2Models[i] != 0)
			delete MD2Models[i];

	MD2Models.clear();

	if (VertexDeclarationMD2 != 0) {
		VertexDeclarationMD2->Release();
		VertexDeclarationMD2 = 0;
	}

	for (uint i = 0; i < Textures.size(); ++i)
		if (Textures[i] != 0)
			delete Textures[i];

	Textures.clear();

	if (d3ddev != 0)
		d3ddev->Release();

	if (d3ddev != 0)
		d3d->Release();

	d3ddev = 0;
	d3d    = 0;

	delete flush;
	delete hook;
}

const char* MADLLMain::returnStr(std::string str)
{
	return (retStr = str).c_str();
}

bool MADLLMain::isInitialized()
{
	return flags & FlagInitialized;
}
