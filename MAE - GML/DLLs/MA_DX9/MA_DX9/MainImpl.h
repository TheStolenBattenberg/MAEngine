#pragma once

#include "Main.h"

#include <list>

class MainImpl: public Main
{
public:
	MainImpl(LPDIRECT3DDEVICE9 d3ddev);
	~MainImpl();

	uint release();

	ErrorCode surfaceCreate(class Surface*& surf);
	ErrorCode surfaceExists(const class Surface* surf, bool& exists);
	void surfaceRemove(const class Surface* surf);

	ErrorCode setError(ErrorCode code);
	ErrorCode getError();

private:
	ErrorCode errCode;
	std::list<class SurfaceImpl*> surfaces;
};
