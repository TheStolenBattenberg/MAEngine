#include "Main.h"
#include "Hook.h"
#include "Resources.h"
#include "ModelMD2.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexDecl.h"
#include "Utils.h"
#include "ModelMPM.h"
#include "ModelX.h"
#include "ParticleSystem.h"

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
	ClearVector(MPMModels);
	ClearVector(Surfaces);
	ClearVector(Textures);
	ClearVector(Light);
	ClearVector(Material);
	ClearVector(Buffers);
	ClearVector(VertexDeclarations);
	ClearVector(VertexBuffers);
	ClearVector(XModels);
	ClearVector(ParticleSys);

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
