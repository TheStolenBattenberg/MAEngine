#pragma once

#include <d3d9.h>
#include <stack>

#include "Variant.h"
#include "Types.h"

enum D3DHooksActions
{
	D3DHookFetchVertexBufferCreate = 0x01,
	D3DHookFetchTextureSet         = 0x02
};

class D3DHooks
{
public:
	D3DHooks(LPDIRECT3DDEVICE9 dev);
	~D3DHooks();

	/**
	 * Enables a action
	 */

	void apply(D3DHooksActions a);

	/**
	 * Disables a action
	 */

	void remove(D3DHooksActions a);

	/**
	 * Makes this object the current one. Must be called in order to achieve anything.
	 */

	void makeCurrent();

	std::stack<Variant> values;

protected:
	void releaseHooks();

private:
	void hook();

	LPDIRECT3DDEVICE9 dev;

	uint actions       = 0;
	uint hookedActions = 0;
};
