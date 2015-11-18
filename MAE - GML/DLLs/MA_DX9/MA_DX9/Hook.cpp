#define CINTERFACE

#include "Hook.h"

#include <stack>

Hook* hookObj = 0;

struct
{
	HRESULT(_stdcall *CreateVertexBuffer)(LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle);
	HRESULT(_stdcall *SetTexture)(LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture);
	HRESULT(_stdcall *SetStreamSource)(LPDIRECT3DDEVICE9 This, UINT StreamNumber, LPDIRECT3DVERTEXBUFFER9 pStreamData, UINT OffsetInBytes, UINT Stride);
	HRESULT(_stdcall *DrawPrimitive)(LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
} originalFunctions;

Hook::Hook(LPDIRECT3DDEVICE9 dev)
{
	this->dev = dev;
	dev->lpVtbl->AddRef(dev);

	hookObj = this;
}

Hook::~Hook()
{
	if (hookedActions & FetchVertexBufferCreate)
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~FetchVertexBufferCreate;
	}

	if (hookedActions & FetchTextureSet)
	{
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;
		hookedActions &= ~FetchTextureSet;
	}

	if (hookedActions & IgnoreVertexBuffer)
	{
		dev->lpVtbl->SetStreamSource = originalFunctions.SetStreamSource;
		dev->lpVtbl->DrawPrimitive = originalFunctions.DrawPrimitive;
		hookedActions &= ~IgnoreVertexBuffer;
	}

	dev->lpVtbl->Release(dev);

	hookObj = 0;
}

bool Hook::enable(Actions a)
{
	if ((a & IgnoreVertexBuffer) && propertys.find(IgnoreedVertexBuffer) == propertys.end())
		return 0;

	actions |= a;
	hook();

	return 1;
}

void Hook::disable(Actions a)
{
	actions &= ~a;
	hook();
}

bool Hook::set(Propertys prop, Variant& v)
{
	switch (prop)
	{
	case IgnoreedVertexBuffer:
		if (v.getType() != Variant::TypePointer)
			return 0;

		propertys[prop] = v;

		return 1;
	}

	return 0;
}

void Hook::hook() {
	if ((actions & FetchVertexBufferCreate) && !(hookedActions & FetchVertexBufferCreate))
	{
		originalFunctions.CreateVertexBuffer = dev->lpVtbl->CreateVertexBuffer;

		dev->lpVtbl->CreateVertexBuffer = [](LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle) -> HRESULT
		{
			HRESULT res = originalFunctions.CreateVertexBuffer(This, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

			if (SUCCEEDED(res))
			{
				(*ppVertexBuffer)->lpVtbl->AddRef(*ppVertexBuffer);
				hookObj->values.push((void*)*ppVertexBuffer);
			}

			return res;
		};

		hookedActions |= FetchVertexBufferCreate;
	}

	if (!(actions & FetchVertexBufferCreate) && (hookedActions & FetchVertexBufferCreate))
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedActions &= ~FetchVertexBufferCreate;
	}

	if ((actions & FetchTextureSet) && !(hookedActions & FetchTextureSet))
	{
		originalFunctions.SetTexture = dev->lpVtbl->SetTexture;

		dev->lpVtbl->SetTexture = [](LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture) -> HRESULT
		{
			pTexture->lpVtbl->AddRef(pTexture);
			hookObj->values.push((void*) pTexture);

			return originalFunctions.SetTexture(This, Sampler, pTexture);
		};

		hookedActions |= FetchTextureSet;
	}

	if (!(actions & FetchTextureSet) && (hookedActions & FetchTextureSet))
	{
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;
		hookedActions &= ~FetchTextureSet;
	}

	if ((actions & IgnoreVertexBuffer) && !(hookedActions & IgnoreVertexBuffer))
	{
		hookObj->propertys[IgnoreNextDrawCall] = Variant((int) 0);

		originalFunctions.SetStreamSource = dev->lpVtbl->SetStreamSource;
		originalFunctions.DrawPrimitive   = dev->lpVtbl->DrawPrimitive;

		dev->lpVtbl->SetStreamSource = [](LPDIRECT3DDEVICE9 This, UINT StreamNumber, LPDIRECT3DVERTEXBUFFER9 pStreamData, UINT OffsetInBytes, UINT Stride) -> HRESULT
		{
			if (hookObj->propertys[IgnoreedVertexBuffer].getPointer() == pStreamData)
			{
				hookObj->propertys[IgnoreNextDrawCall] = Variant((int) 1);
				return D3D_OK;
			}

			return originalFunctions.SetStreamSource(This, StreamNumber, pStreamData, OffsetInBytes, Stride);
		};

		dev->lpVtbl->DrawPrimitive = [](LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)->HRESULT
		{
			if (hookObj->propertys[IgnoreNextDrawCall].getInteger())
			{
				hookObj->propertys[IgnoreNextDrawCall] = Variant((int) 0);
				return D3D_OK;
			}

			return originalFunctions.DrawPrimitive(This, PrimitiveType, StartVertex, PrimitiveCount);
		};

		hookedActions |= IgnoreVertexBuffer;
	}

	if (!(actions & IgnoreVertexBuffer) && (hookedActions & IgnoreVertexBuffer))
	{
		dev->lpVtbl->SetStreamSource = originalFunctions.SetStreamSource;
		dev->lpVtbl->DrawPrimitive = originalFunctions.DrawPrimitive;
		hookedActions &= ~IgnoreVertexBuffer;
	}
}
