#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <vector>

#include "CMesh.h"
#include "Types.h"

class CModelLoadMSM {
public:
	void Load(std::vector<Mesh> *mesh, string file);
};