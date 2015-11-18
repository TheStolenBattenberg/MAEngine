#pragma once

#include "Hook.h"

class Flush
{
public:
	~Flush();

	void beginFetch();
	void endFetch();

private:
	LPDIRECT3DVERTEXBUFFER9 vb = 0;
};
