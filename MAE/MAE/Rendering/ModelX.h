#pragma once

/**
* Includes
*/

#include <MAE/Core/Types.h>
#include <d3dx9.h>

#include <string>

class XModel {
public:
	XModel(class Renderer* renderer): renderer(renderer) { }
	~XModel();

	bool load(std::string filename, std::string texturedir);

	LPD3DXMESH getMesh();
	D3DMATERIAL9* getMaterial(uint index);
	LPDIRECT3DTEXTURE9 getTexture(uint index);

	DWORD getMaterialCount();
private:
	class Renderer* renderer;

	DWORD materialCount;

	LPD3DXMESH          mesh = nullptr;
	D3DMATERIAL9*       materials = nullptr;
	LPDIRECT3DTEXTURE9* textures = nullptr;
};