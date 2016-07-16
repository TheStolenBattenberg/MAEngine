#include <MAE/Main.h>
#include <MAE/Rendering/ModelX.h>
#include <MAE/Rendering/RendererImpl.h>

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
		mesh = 0;
	}
}

bool XModel::load(std::string filename, std::string texturedir) {
	auto device = ((RendererImpl*) renderer)->getDevice();

	LPD3DXBUFFER materialBuffer;

	HRESULT res;
	res = D3DXLoadMeshFromX(filename.c_str(), D3DXMESH_SYSTEMMEM, device, NULL, &materialBuffer, NULL, &materialCount, &mesh);

	if (FAILED(res)) {
		// TODO: Add proper error checking
		return false;
	}

	D3DXMATERIAL* xMaterials = (D3DXMATERIAL* )materialBuffer->GetBufferPointer();

	materials = new D3DMATERIAL9[materialCount];
	textures  = new LPDIRECT3DTEXTURE9[materialCount];

	memset(materials, 0, materialCount * sizeof(D3DMATERIAL9));
	memset(textures, 0, materialCount * sizeof(LPDIRECT3DTEXTURE9));

	for (uint i = 0; i < materialCount; ++i) {
		materials[i] = xMaterials[i].MatD3D;
		materials[i].Ambient = D3DXCOLOR(0.0, 0.0, 0.0, 0.0);

		textures[i] = NULL;
		if (xMaterials[i].pTextureFilename != NULL && lstrlen(xMaterials[i].pTextureFilename) > 0) {
			std::string file = texturedir + '/' + xMaterials[i].pTextureFilename;

			res = D3DXCreateTextureFromFile(device, file.c_str(), &textures[i]);

			// TODO: Add proper error checking
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
