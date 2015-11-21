#define CINTERFACE

#include "Hook.h"

#include <stack>

Hook* hookObj = 0;

struct
{
	HRESULT(_stdcall *CreateTexture)(LPDIRECT3DDEVICE9 This, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE9* ppTexture, HANDLE* pSharedHandle);
	HRESULT(_stdcall *CreateVertexBuffer)(LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle);
	HRESULT(_stdcall *DrawPrimitive)(LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
	HRESULT(_stdcall *SetTexture)(LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture);
	HRESULT(_stdcall *SetStreamSource)(LPDIRECT3DDEVICE9 This, UINT StreamNumber, LPDIRECT3DVERTEXBUFFER9 pStreamData, UINT OffsetInBytes, UINT Stride);
} originalFunctions;

Hook::Hook(LPDIRECT3DDEVICE9 dev)
{
	this->dev = dev;
	dev->lpVtbl->AddRef(dev);

	hookObj = this;
}

Hook::~Hook()
{
	if (hookedFuncs & HookedFuncCreateTex)
		dev->lpVtbl->CreateTexture = originalFunctions.CreateTexture;

	if (hookedFuncs & HookedFuncCreateVB)
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;

	if (hookedFuncs & HookedFuncDrawPrim)
		dev->lpVtbl->DrawPrimitive = originalFunctions.DrawPrimitive;

	if (hookedFuncs & HookedFuncSetStreamSrc)
		dev->lpVtbl->SetStreamSource = originalFunctions.SetStreamSource;

	if (hookedFuncs & HookedFuncSetTex)
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;

	hookedFuncs = 0;

	for (auto i: redirectTex)
		i.second->lpVtbl->Release(i.second);

	for (auto i: redirectVB)
		i.second->lpVtbl->Release(i.second);

	dev->lpVtbl->Release(dev);

	hookObj = 0;
}

bool Hook::enable(Actions a)
{
	if ((a & ActionForceTexPool) && propertys.find(PropertyForceTexPool) == propertys.end())
		return 0;

	if ((a & ActionForceVBPool) && propertys.find(PropertyForceVBPool) == propertys.end())
		return 0;

	if ((a & ActionRedirectTexture))
		invalidTex = 0;

	if ((a & ActionRedirectVertexBuffer))
		invalidVB = 0;

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
	LPDIRECT3DVERTEXBUFFER9 pVB  = 0;
	LPDIRECT3DBASETEXTURE9  pTex = 0;

	switch (prop)
	{
	case PropertyRedirectVBFrom:
		if (v.getType() != Variant::TypePointer)
			return 0;

		curVB = (LPDIRECT3DVERTEXBUFFER9) v.getPointer();
		redirectVB[curVB] = 0;

		return 1;
	case PropertyRedirectVBTo:
		if (curVB == 0 || v.getType() != Variant::TypePointer)
			return 0;

		pVB = (LPDIRECT3DVERTEXBUFFER9) v.getPointer();

		pVB->lpVtbl->AddRef(pVB);

		redirectVB[curVB] = pVB;

		return 1;
	case PropertyRedirectVBRemove:
		if (v.getType() != Variant::TypePointer)
			return 0;

		if (redirectVB.find((LPDIRECT3DVERTEXBUFFER9) v.getPointer()) == redirectVB.end())
			return 0;

		pVB = redirectVB[(LPDIRECT3DVERTEXBUFFER9) v.getPointer()];

		pVB->lpVtbl->Release(pVB);
		redirectVB.erase((LPDIRECT3DVERTEXBUFFER9) v.getPointer());

		return 1;
	case PropertyRedirectTexFrom:
		if (v.getType() != Variant::TypePointer)
			return 0;

		curTex = (LPDIRECT3DBASETEXTURE9) v.getPointer();
		redirectTex[curTex] = 0;

		return 1;
	case PropertyRedirectTexTo:
		if (curTex == 0 || v.getType() != Variant::TypePointer)
			return 0;

		pTex = (LPDIRECT3DBASETEXTURE9) v.getPointer();

		pTex->lpVtbl->AddRef(pTex);

		redirectTex[curTex] = pTex;

		return 1;
	case PropertyRedirectTexRemove:
		if (v.getType() != Variant::TypePointer)
			return 0;

		if (redirectTex.find((LPDIRECT3DBASETEXTURE9) v.getPointer()) == redirectTex.end())
			return 0;

		pTex = redirectTex[(LPDIRECT3DBASETEXTURE9) v.getPointer()];

		pTex->lpVtbl->Release(pTex);
		redirectTex.erase((LPDIRECT3DBASETEXTURE9) v.getPointer());

		return 1;
	case PropertyForceTexPool:
		if (v.getType() != Variant::TypeInteger)
			return 0;

		propertys[PropertyForceTexPool] = v;

		return 1;
	case PropertyForceVBPool:
		if (v.getType() != Variant::TypeInteger)
			return 0;

		propertys[PropertyForceVBPool] = v;

		return 1;
	}

	return 0;
}

void Hook::hook() {
	
	/**
	 * CreateVertexBuffer Hook
	 */

	if ((actions & ActionFetchVBCreate || actions & ActionForceVBPool) && !(hookedFuncs & HookedFuncCreateVB))
	{
		originalFunctions.CreateVertexBuffer = dev->lpVtbl->CreateVertexBuffer;

		dev->lpVtbl->CreateVertexBuffer = [](LPDIRECT3DDEVICE9 This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER9* ppVertexBuffer, HANDLE* pSharedHandle) -> HRESULT
		{
			if (hookObj->actions & ActionForceVBPool)
				Pool = (D3DPOOL) hookObj->propertys[PropertyForceVBPool].getInteger();

			HRESULT res = originalFunctions.CreateVertexBuffer(This, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

			if (hookObj->actions & ActionFetchVBCreate)
			{
				if (SUCCEEDED(res))
				{
					(*ppVertexBuffer)->lpVtbl->AddRef(*ppVertexBuffer);
					hookObj->values.push((void*) *ppVertexBuffer);
				}
			}

			return res;
		};

		hookedFuncs |= HookedFuncCreateVB;
	}

	if (!(actions & ActionFetchVBCreate) && !(actions & ActionForceVBPool) && (hookedFuncs & HookedFuncCreateVB))
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedFuncs &= ~HookedFuncCreateVB;
	}

	/**
	 * SetTexture Hook
	 */

	if ((actions & ActionFetchTexSet || actions & ActionRedirectTexture) && !(hookedFuncs & HookedFuncSetTex))
	{
		originalFunctions.SetTexture = dev->lpVtbl->SetTexture;

		dev->lpVtbl->SetTexture = [](LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture) -> HRESULT
		{
			if (hookObj->actions & ActionFetchTexSet)
			{
				pTexture->lpVtbl->AddRef(pTexture);
				hookObj->values.push((void*) pTexture);
			}

			if (hookObj->actions & ActionRedirectTexture)
			{
				hookObj->invalidTex &= ~(1 << Sampler);

				if (hookObj->redirectTex.find(pTexture) != hookObj->redirectTex.end())
				{
					LPDIRECT3DBASETEXTURE9 tex = hookObj->redirectTex[pTexture];

					if (tex == 0)
					{
						hookObj->invalidTex |= 1 << Sampler;
						return D3D_OK;
					}
					else
						return originalFunctions.SetTexture(This, Sampler, tex);
				}
			}

			return originalFunctions.SetTexture(This, Sampler, pTexture);
		};

		hookedFuncs |= HookedFuncSetTex;
	}

	if (!(actions & ActionFetchTexSet) && !(actions & ActionRedirectTexture) && (hookedFuncs & HookedFuncSetTex))
	{
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;
		hookedFuncs &= ~HookedFuncSetTex;
	}

	/**
	 * SetStreamSource Hook
	 */

	if ((actions & ActionRedirectVertexBuffer) && !(hookedFuncs & HookedFuncSetStreamSrc))
	{
		originalFunctions.SetStreamSource = dev->lpVtbl->SetStreamSource;

		dev->lpVtbl->SetStreamSource = [](LPDIRECT3DDEVICE9 This, UINT StreamNumber, LPDIRECT3DVERTEXBUFFER9 pStreamData, UINT OffsetInBytes, UINT Stride) -> HRESULT
		{
			hookObj->invalidVB &= ~(1 << StreamNumber);

			if (hookObj->redirectVB.find(pStreamData) != hookObj->redirectVB.end())
			{
				LPDIRECT3DVERTEXBUFFER9 vb = hookObj->redirectVB[pStreamData];

				if (vb == 0)
				{
					hookObj->invalidVB |= 1 << StreamNumber;
					return D3D_OK;
				}
				else
					return originalFunctions.SetStreamSource(This, StreamNumber, vb, OffsetInBytes, Stride);
			}

			return originalFunctions.SetStreamSource(This, StreamNumber, pStreamData, OffsetInBytes, Stride);
		};

		hookedFuncs |= HookedFuncSetStreamSrc;
	}

	if (!(actions & ActionRedirectVertexBuffer) && (hookedFuncs & HookedFuncSetStreamSrc))
	{
		dev->lpVtbl->SetStreamSource = originalFunctions.SetStreamSource;
		hookedFuncs &= ~HookedFuncSetStreamSrc;
	}

	/**
	 * DrawPrimitive Hook
	 */

	if ((actions & ActionRedirectTexture || actions & ActionRedirectVertexBuffer) && !(hookedFuncs & HookedFuncDrawPrim))
	{
		originalFunctions.DrawPrimitive = dev->lpVtbl->DrawPrimitive;

		dev->lpVtbl->DrawPrimitive = [](LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)->HRESULT
		{
			if (((hookObj->actions & ActionRedirectTexture) && hookObj->invalidTex != 0) ||
				(hookObj->actions & ActionRedirectVertexBuffer) && hookObj->invalidVB != 0) {
				
				return D3D_OK;
			}
			
			return originalFunctions.DrawPrimitive(This, PrimitiveType, StartVertex, PrimitiveCount);
		};

		hookedFuncs |= HookedFuncDrawPrim;
	}

	if (!(actions & ActionRedirectTexture) && !(actions & ActionRedirectVertexBuffer) && (hookedFuncs & HookedFuncDrawPrim))
	{
		dev->lpVtbl->SetStreamSource = originalFunctions.SetStreamSource;
		hookedFuncs &= ~HookedFuncDrawPrim;
	}

	/**
	* CreateTexture Hook
	*/

	if ((actions & ActionFetchTexCreate || actions & ActionForceTexPool) && !(hookedFuncs & HookedFuncCreateTex))
	{
		originalFunctions.CreateTexture = dev->lpVtbl->CreateTexture;

		dev->lpVtbl->CreateTexture = [](LPDIRECT3DDEVICE9 This, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE9* ppTexture, HANDLE* pSharedHandle) -> HRESULT
		{
			if (hookObj->actions & ActionForceTexPool)
				Pool = (D3DPOOL) hookObj->propertys[PropertyForceTexPool].getInteger();

			HRESULT res = originalFunctions.CreateTexture(This, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

			if (hookObj->actions & ActionFetchTexCreate)
			{
				if (SUCCEEDED(res))
				{
					(*ppTexture)->lpVtbl->AddRef(*ppTexture);
					hookObj->values.push((void*) *ppTexture);
				}
			}

			return res;
		};

		hookedFuncs |= HookedFuncCreateTex;
	}

	if (!(actions & ActionFetchTexCreate) && !(actions & ActionForceTexPool) && (hookedFuncs & HookedFuncCreateTex))
	{
		dev->lpVtbl->CreateVertexBuffer = originalFunctions.CreateVertexBuffer;
		hookedFuncs &= ~HookedFuncCreateTex;
	}
}
