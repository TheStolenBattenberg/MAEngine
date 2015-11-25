#include "Main.h"

XModel::~XModel()
{
	for (uint i = 0; i < materialCount; ++i) {
		if (textures[i] != NULL) {
			textures[i]->Release();
		}
	}
	delete[] textures;
	
	if (materials != NULL) {
		delete[] materials;
	}

	if (mesh != NULL) {
		mesh->Release();
		delete mesh;
	}
}

bool XModel::load(std::string filename, std::string texturedir) {
	LPD3DXBUFFER materialBuffer;

	HRESULT res;
	res = D3DXLoadMeshFromX(filename.c_str(), D3DXMESH_SYSTEMMEM, mamain->d3ddev, NULL, &materialBuffer, NULL, &materialCount, &mesh);
	if (FAILED(res)) {
		mamain->err.onErrorDX9("Couldn't load .X mesh. ", res);
		return false;
	}

	D3DXMATERIAL* xMaterials = (D3DXMATERIAL* )materialBuffer->GetBufferPointer();
	materials = new D3DMATERIAL9[materialCount];
	textures = new LPDIRECT3DTEXTURE9[materialCount];
	if (materials == NULL || textures == NULL) {
		mamain->err.onError("Out of memory!");
		return false;
	}

	for (uint i = 0; i < materialCount; ++i) {
		materials[i] = xMaterials[i].MatD3D;
		materials[i].Ambient = D3DXCOLOR(0.0, 0.0, 0.0, 0.0);

		textures[i] = NULL;
		if (xMaterials[i].pTextureFilename != NULL && lstrlen(xMaterials[i].pTextureFilename) > 0) {
			res = D3DXCreateTextureFromFile(mamain->d3ddev, xMaterials[i].pTextureFilename, &textures[i]);
			if (FAILED(res)) {
				mamain->err.onErrorDX9("Couldn't load .X texture.", res);
			}
		}
	}

	materialBuffer->Release();
	return true;
}

DWORD XModel::getMaterialCount() {
	return materialCount;
}

LPD3DXMESH  XModel::getMesh() {
	return mesh;
}

D3DMATERIAL9  XModel::getMaterial(uint index) {
	return materials[index];
}

LPDIRECT3DTEXTURE9  XModel::getTexture(uint index) {
	return textures[index];
}