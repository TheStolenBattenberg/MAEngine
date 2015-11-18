#pragma once

#include <d3d9.h>
#include <stack>
#include <map>

#include "Variant.h"
#include "Types.h"

class D3DHook
{
public:
	enum Actions
	{
		FetchVertexBufferCreate = 0x01,
		FetchTextureSet         = 0x02,
		IgnoreVertexBuffer      = 0x04
	};

	enum Propertys
	{
		IgnoreedVertexBuffer = 0x00,
		IgnoreNextDrawCall   = 0x01
	};

	D3DHook(LPDIRECT3DDEVICE9 dev);
	~D3DHook();

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

	std::map<Propertys, Variant> propertys;

private:
	void hook();

	LPDIRECT3DDEVICE9 dev;

	uint actions       = 0;
	uint hookedActions = 0;
};
