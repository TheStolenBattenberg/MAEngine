#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "CMesh.h"
#include "Types.h"

class CModel {
public:
	void Render();
	void Destroy();
	void Update();

private:
	uint m_uiMaterialCount;
	uint m_uiMeshCount;


	std::vector<Mesh> m_vMeshs;
	std::vector<Material> m_vMaterials;
};