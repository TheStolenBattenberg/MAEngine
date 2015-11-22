#define CINTERFACE

#include "Hook.h"

#include <stack>

Hook* hookObj = 0;

struct
{
	HRESULT(_stdcall *CreateTexture)(LPDIRECT3DDEVICE9 This, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE9* ppTexture, HANDLE* pSharedHandle);
	HRESULT(_stdcall *CreateVertexDeclaration)(LPDIRECT3DDEVICE9 This, CONST D3DVERTEXELEMENT9* pVertexElements, LPDIRECT3DVERTEXDECLARATION9* ppDecl);
	HRESULT(_stdcall *DrawPrimitive)(LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
	HRESULT(_stdcall *SetTexture)(LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture);
	HRESULT(_stdcall *SetVertexDeclaration)(LPDIRECT3DDEVICE9 This, LPDIRECT3DVERTEXDECLARATION9 pDecl);
	HRESULT(_stdcall *SetFVF)(LPDIRECT3DDEVICE9 This, DWORD FVF);
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

	if (hookedFuncs & HookedFuncCreateVertDecl)
		dev->lpVtbl->CreateVertexDeclaration = originalFunctions.CreateVertexDeclaration;

	if (hookedFuncs & HookedFuncDrawPrim)
		dev->lpVtbl->DrawPrimitive = originalFunctions.DrawPrimitive;

	if (hookedFuncs & HookedFuncSetFVF)
		dev->lpVtbl->SetFVF = originalFunctions.SetFVF;

	if (hookedFuncs & HookedFuncSetTex)
		dev->lpVtbl->SetTexture = originalFunctions.SetTexture;

	if (hookedFuncs & HookedFuncSetVertDecl)
		dev->lpVtbl->SetVertexDeclaration = originalFunctions.SetVertexDeclaration;

	hookedFuncs = 0;

	for (auto i: redirectTex)
		if (i.second != 0)
			i.second->lpVtbl->Release(i.second);

	dev->lpVtbl->Release(dev);

	hookObj = 0;
}

bool Hook::enable(Actions a)
{
	if ((a & ActionForceTexPool) && propertys.find(PropertyForceTexPool) == propertys.end())
		return 0;

	if ((a & ActionRedirectTexture))
		invalidTex = 0;

	if ((a & ActionIgnoreVertDecl))
		isInvalidDecl = 0;

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
	LPDIRECT3DBASETEXTURE9  pTex = 0;

	switch (prop)
	{
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
	case PropertyDisableVertDecl:
		if (v.getType() != Variant::TypePointer)
			return 0;

		for (auto i: invalidDecl)
			if (i == v.getPointer())
				return 1;

		invalidDecl.push_back((LPDIRECT3DVERTEXDECLARATION9) v.getPointer());

		return 1;
	case PropertyEnableVertDecl:
		if (v.getType() != Variant::TypePointer)
			return 0;

		for (auto i = invalidDecl.begin(); i != invalidDecl.end(); ++i)
		{
			if (*i == v.getPointer())
			{
				invalidDecl.erase(i);
				return 1;
			}
		}

		return 0;
	}

	return 0;
}

void Hook::hook() {
	
	/**
	 * SetTexture Hook
	 */

	if ((actions & ActionFetchTexSet || actions & ActionRedirectTexture) && !(hookedFuncs & HookedFuncSetTex))
	{
		originalFunctions.SetTexture = dev->lpVtbl->SetTexture;

		dev->lpVtbl->SetTexture = [](LPDIRECT3DDEVICE9 This, DWORD Sampler, LPDIRECT3DBASETEXTURE9 pTexture) -> HRESULT
		{
			if (pTexture == 0)
				return originalFunctions.SetTexture(This, Sampler, pTexture);

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
	 * DrawPrimitive Hook
	 */

	if ((actions & ActionRedirectTexture || actions & ActionIgnoreVertDecl) && !(hookedFuncs & HookedFuncDrawPrim))
	{
		originalFunctions.DrawPrimitive = dev->lpVtbl->DrawPrimitive;

		dev->lpVtbl->DrawPrimitive = [](LPDIRECT3DDEVICE9 This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)->HRESULT
		{
			if (((hookObj->actions & ActionRedirectTexture) && hookObj->invalidTex != 0) ||
				(hookObj->actions & ActionIgnoreVertDecl) && hookObj->isInvalidDecl) {
				
				return D3D_OK;
			}
			
			return originalFunctions.DrawPrimitive(This, PrimitiveType, StartVertex, PrimitiveCount);
		};

		hookedFuncs |= HookedFuncDrawPrim;
	}

	if (!(actions & ActionRedirectTexture) && !(actions & ActionIgnoreVertDecl) && (hookedFuncs & HookedFuncDrawPrim))
	{
		dev->lpVtbl->DrawPrimitive = originalFunctions.DrawPrimitive;
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
		dev->lpVtbl->CreateTexture = originalFunctions.CreateTexture;
		hookedFuncs &= ~HookedFuncCreateTex;
	}

	/**
	 * CreateVertexDeclaration
	 */

	if (actions & ActionFetchVertDecl && !(hookedFuncs & HookedFuncCreateVertDecl))
	{
		originalFunctions.CreateVertexDeclaration = dev->lpVtbl->CreateVertexDeclaration;

		dev->lpVtbl->CreateVertexDeclaration = [](LPDIRECT3DDEVICE9 This, CONST D3DVERTEXELEMENT9* pVertexElements, LPDIRECT3DVERTEXDECLARATION9* ppDecl) -> HRESULT
		{
			HRESULT res = originalFunctions.CreateVertexDeclaration(This, pVertexElements, ppDecl);

			if (SUCCEEDED(res))
			{
				(*ppDecl)->lpVtbl->AddRef(*ppDecl);
				hookObj->values.push(*ppDecl);
			}

			return res;
		};

		hookedFuncs |= HookedFuncCreateVertDecl;
	}

	if (!(actions & ActionFetchVertDecl) && (hookedFuncs & HookedFuncCreateVertDecl))
	{
		dev->lpVtbl->CreateVertexDeclaration = originalFunctions.CreateVertexDeclaration;
		hookedFuncs &= ~HookedFuncCreateVertDecl;
	}

	/**
	 * SetVertexDeclaration
	 */

	if (actions & ActionIgnoreVertDecl && !(hookedFuncs & HookedFuncSetVertDecl))
	{
		originalFunctions.SetVertexDeclaration = dev->lpVtbl->SetVertexDeclaration;

		dev->lpVtbl->SetVertexDeclaration = [](LPDIRECT3DDEVICE9 This, LPDIRECT3DVERTEXDECLARATION9 pDecl) -> HRESULT
		{
			hookObj->isInvalidDecl = 0;

			for (auto i : hookObj->invalidDecl)
			{
				if (i == pDecl)
				{
					hookObj->isInvalidDecl = 1;
					break;
				}
			}

			return originalFunctions.SetVertexDeclaration(This, pDecl);
		};

		hookedFuncs |= HookedFuncSetVertDecl;
	}

	if (!(actions & ActionIgnoreVertDecl) && (hookedFuncs & HookedFuncSetVertDecl))
	{
		dev->lpVtbl->SetVertexDeclaration = originalFunctions.SetVertexDeclaration;
		hookedFuncs &= ~HookedFuncSetVertDecl;
	}

	/**
	 * SetFVF
	 */

	if (actions & ActionIgnoreVertDecl && !(hookedFuncs & HookedFuncSetFVF))
	{
		originalFunctions.SetFVF = dev->lpVtbl->SetFVF;

		dev->lpVtbl->SetFVF = [](LPDIRECT3DDEVICE9 This, DWORD FVF) -> HRESULT
		{
			hookObj->isInvalidDecl = 0;

			return originalFunctions.SetFVF(This, FVF);
		};

		hookedFuncs |= HookedFuncSetFVF;
	}

	if (!(actions & ActionIgnoreVertDecl) && (hookedFuncs & HookedFuncSetFVF))
	{
		dev->lpVtbl->SetFVF = originalFunctions.SetFVF;
		hookedFuncs &= ~HookedFuncSetFVF;
	}
}
