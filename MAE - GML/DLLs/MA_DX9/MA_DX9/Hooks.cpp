#define CINTERFACE

#include "Hooks.h"

#include <stack>

D3DHooks* curObj = 0;

struct
{
	HRESULT(_stdcall *CreateVertexBuffer)(IDirect3DDevice9* This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle);
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
	if (hookedActions & D3DHookFetchVertexBuffer)
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~D3DHookFetchVertexBuffer;
	}
}

void D3DHooks::hook() {
	if ((actions & D3DHookFetchVertexBuffer) && !(hookedActions & D3DHookFetchVertexBuffer))
	{
		originalFunctions.CreateVertexBuffer = dev->lpVtbl->CreateVertexBuffer;

		dev->lpVtbl->CreateVertexBuffer = [](IDirect3DDevice9* This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) -> HRESULT
		{
			HRESULT res = originalFunctions.CreateVertexBuffer(This, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

			(*ppVertexBuffer)->lpVtbl->AddRef(*ppVertexBuffer);
			
			curObj->values.push((void*)*ppVertexBuffer);

			return res;
		};

		hookedActions |= D3DHookFetchVertexBuffer;
	}

	if (!(actions & D3DHookFetchVertexBuffer) && (hookedActions & D3DHookFetchVertexBuffer))
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~D3DHookFetchVertexBuffer;
	}
}
