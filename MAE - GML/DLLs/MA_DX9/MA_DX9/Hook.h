#pragma once

#include <d3d9.h>
#include <stack>
#include <map>

#include "Variant.h"
#include "Types.h"

class Hook
{
public:
	enum Actions
	{
		ActionFetchVBCreate        = 0x01,
		ActionFetchTexSet          = 0x02,
		ActionFetchTexCreate       = 0x04,
		ActionRedirectVertexBuffer = 0x08,
		ActionRedirectTexture      = 0x10,
		ActionForceTexPool         = 0x20,
		ActionForceVBPool          = 0x40
	};

	enum Propertys
	{
		PropertyRedirectVBFrom    = 0x01,
		PropertyRedirectVBTo      = 0x02,
		PropertyRedirectVBRemove  = 0x03,
		PropertyRedirectTexFrom   = 0x04,
		PropertyRedirectTexTo     = 0x05,
		PropertyRedirectTexRemove = 0x06,
		PropertyForceTexPool      = 0x07,
		PropertyForceVBPool       = 0x08
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
		HookedFuncCreateTex    = 0x01,
		HookedFuncCreateVB     = 0x02,
		HookedFuncDrawPrim     = 0x04,
		HookedFuncSetTex       = 0x08,
		HookedFuncSetStreamSrc = 0x10
	};

	void hook();

	LPDIRECT3DDEVICE9 dev;

	uint hookedFuncs = 0;

	LPDIRECT3DBASETEXTURE9 curTex = 0;
	LPDIRECT3DVERTEXBUFFER9 curVB = 0;

protected:
	uint actions = 0;

	uint invalidVB  = 0;
	uint invalidTex = 0;

	std::map<LPDIRECT3DBASETEXTURE9, LPDIRECT3DBASETEXTURE9>   redirectTex;
	std::map<LPDIRECT3DVERTEXBUFFER9, LPDIRECT3DVERTEXBUFFER9> redirectVB;

	std::map<Propertys, Variant> propertys;
};
