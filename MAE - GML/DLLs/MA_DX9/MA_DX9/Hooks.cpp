#define CINTERFACE

#include "Hooks.h"

#include <stack>

D3DHooks* curObj = 0;

struct
{
	HRESULT(_stdcall *CreateVertexBuffer)(LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle);
	HRESULT(_stdcall *SetTexture)(LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture);
} originalFunctions;

D3DHooks::D3DHooks(LPDIRECT3DDEVICE9 dev)
{
	this->dev = dev;
}

D3DHooks::~D3DHooks()
{
	if (curObj == this)
	{
		curObj->releaseHooks();
		curObj = 0;
	}
}

void D3DHooks::apply(D3DHooksActions a)
{
	actions |= a;

	if (curObj == this)
		hook();
}

void D3DHooks::remove(D3DHooksActions a)
{
	actions &= ~a;
	
	if (curObj == this)
		hook();
}

void D3DHooks::makeCurrent()
{
	if (curObj != this) {
		if (curObj != 0)
			curObj->releaseHooks();

		curObj = this;
		hook();
	}
}

void D3DHooks::releaseHooks() {
	if (hookedActions & D3DHookFetchVertexBufferCreate)
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~D3DHookFetchVertexBufferCreate;
	}

	if (hookedActions & D3DHookFetchTextureSet)
	{
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;
		hookedActions &= ~D3DHookFetchTextureSet;
	}
}

void D3DHooks::hook() {
	if ((actions & D3DHookFetchVertexBufferCreate) && !(hookedActions & D3DHookFetchVertexBufferCreate))
	{
		originalFunctions.CreateVertexBuffer = dev->lpVtbl->CreateVertexBuffer;

		dev->lpVtbl->CreateVertexBuffer = [](LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle) -> HRESULT
		{
			HRESULT res = originalFunctions.CreateVertexBuffer(This, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

			if (!FAILED(res))
			{
				(*ppVertexBuffer)->lpVtbl->AddRef(*ppVertexBuffer);
				curObj->values.push((void*)*ppVertexBuffer);
			}
			else
				curObj->values.push((void*) 0);

			return res;
		};

		hookedActions |= D3DHookFetchVertexBufferCreate;
	}

	if (!(actions & D3DHookFetchVertexBufferCreate) && (hookedActions & D3DHookFetchVertexBufferCreate))
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~D3DHookFetchVertexBufferCreate;
	}

	if ((actions & D3DHookFetchTextureSet) && !(hookedActions & D3DHookFetchTextureSet))
	{
		originalFunctions.SetTexture = dev->lpVtbl->SetTexture;

		dev->lpVtbl->SetTexture = [](LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture) -> HRESULT
		{
			HRESULT res = originalFunctions.SetTexture(This, Sampler, pTexture);

			pTexture->lpVtbl->AddRef(pTexture);
			curObj->values.push((void*) pTexture);

			return res;
		};

		hookedActions |= D3DHookFetchTextureSet;
	}

	if (!(actions & D3DHookFetchTextureSet) && (hookedActions & D3DHookFetchTextureSet))
	{
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;
		hookedActions &= ~D3DHookFetchTextureSet;
	}
}
