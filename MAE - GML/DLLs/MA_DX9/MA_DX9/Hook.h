#pragma once

#include <d3d9.h>
#include <stack>
#include <map>
#include <vector>

#include "Variant.h"
#include "Types.h"

class Hook
{
public:
	enum Actions
	{
		ActionFetchTexCreate  = 0x01,
		ActionFetchTexSet     = 0x02,
		ActionFetchVertDecl   = 0x04,
		ActionForceTexPool    = 0x08,
		ActionIgnoreVertDecl  = 0x10,
		ActionRedirectTexture = 0x20
	};

	enum Propertys
	{
		PropertyDisableVertDecl   = 0x01,
		PropertyEnableVertDecl    = 0x02,
		PropertyForceTexPool      = 0x03,
		PropertyRedirectTexFrom   = 0x04,
		PropertyRedirectTexRemove = 0x05,
		PropertyRedirectTexTo     = 0x06
	};

	Hook(LPDIRECT3DDEVICE9 dev);
	~Hook();

	/**
	 * Enables a action
	 */

	bool enable(Actions a);

	/**
	 * Disables a action
	 */

	void disable(Actions a);

	/**
	 * Sets a property to change the behaviour
	 */

	bool set(Propertys prop, Variant& v);

	std::stack<Variant> values;

private:
	enum HookedFunctions
	{
		HookedFuncCreateTex      = 0x01,
		HookedFuncCreateVertDecl = 0x02,
		HookedFuncDrawPrim       = 0x04,
		HookedFuncSetFVF         = 0x08,
		HookedFuncSetTex         = 0x10,
		HookedFuncSetVertDecl    = 0x20
	};

	void hook();

	LPDIRECT3DDEVICE9 dev;

	uint hookedFuncs = 0;

	LPDIRECT3DBASETEXTURE9 curTex = 0;
	LPDIRECT3DVERTEXBUFFER9 curVB = 0;

protected:
	uint actions = 0;

	bool isInvalidDecl = 0;

	uint invalidTex = 0;

	std::map<LPDIRECT3DBASETEXTURE9, LPDIRECT3DBASETEXTURE9> redirectTex;
	
	std::vector<LPDIRECT3DVERTEXDECLARATION9> invalidDecl;

	std::map<Propertys, Variant> propertys;
};
