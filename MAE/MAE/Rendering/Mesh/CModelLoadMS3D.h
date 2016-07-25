#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <vector>

#include <MAE/Rendering/Mesh/CMesh.h>
#include <MAE/Core/Types.h>

class CModelLoadMS3D {
public:
	uint Load(Mesh* mesh, string file);
};