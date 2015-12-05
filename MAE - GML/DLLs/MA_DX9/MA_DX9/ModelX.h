#pragma once

/**
* Includes
*/

#include "Types.h"
#include "Object.h"

class XModel: public Object {
public:
	~XModel();

	bool load(std::string filename, std::string texturedir);

	LPD3DXMESH getMesh();
	D3DMATERIAL9 getMaterial(uint index);
	LPDIRECT3DTEXTURE9 getTexture(uint index);

	DWORD getMaterialCount();
private:
	DWORD materialCount;

	LPD3DXMESH          mesh = NULL;
	D3DMATERIAL9*       materials = NULL;
	LPDIRECT3DTEXTURE9* textures = NULL;
};