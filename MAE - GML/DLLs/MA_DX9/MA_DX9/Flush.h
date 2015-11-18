#pragma once

#include "Hooks.h"

class Flush
{
public:
	~Flush();

	void beginFetch();
	void endFetch();

private:
	LPDIRECT3DVERTEXBUFFER9 vb = 0;
};
