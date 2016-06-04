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
	
	void Load();
	void Save();

private:
	uint m_uiMaterialCount;
	uint m_uiMeshCount;


	std::vector<Mesh> m_vMeshs;
	std::vector<Material> m_vMaterials;
	std::vector<Animation> m_vAnimations;
};

/**
** A quick note on which types of models we should consider adding support for.
** - MPM, MSM. (They're propritory, and support all the features of the engine.  MPM should be the priority.)
** - MD2, MD3. (Vertex Morph Animations, widely used)
** - MD5. (Skeletal Animatons, widely used)
** - MS3D. (Skeletal Animations, strong format, well documented.)
** - OBJ. (Very popular format, though it may be best not to encorage the use of it.)
** - FBX. (Popular Binary format, supports a lot, limited documentation though.)
** - 3DS. (Good binary format, supports a decent chunk of features. Well documented.)
** - U3D. (For cross compatibility with the extension Ultimate3D for Game Maker 5-8.)
** - D3D/gmmod. (For cross compatibility with standard Game Maker 3D.)
**
** Absolutely do not support:
** - X. (We have absolutely no reason to support it.)
**
**/