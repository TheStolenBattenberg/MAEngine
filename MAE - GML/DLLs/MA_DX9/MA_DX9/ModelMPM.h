#pragma once 

/**
 * Includes
 */

#include "Types.h"
#include "Object.h"
#include "Error.h"

#include <d3d9.h>
#include <vector>
#include <Mat.h>
#include <MPM.h>

class MPMModel: public Object
{
public:
	~MPMModel();

	ErrorCode load(const std::string& model);
	void render();

private:
	ErrorCode readInstances(std::ifstream& f);
	ErrorCode readMesh(std::ifstream& f);
	ErrorCode readVertexDesc(std::ifstream& f);
	ErrorCode readVertexData(std::ifstream& f);
	ErrorCode readIndexData(std::ifstream& f);

	struct Mesh
	{
		uint matInd;

		uint numVertices;
		uint numPrim;

		uint stride;

		LPDIRECT3DVERTEXDECLARATION9 decl;
		LPDIRECT3DVERTEXBUFFER9      vb;
		LPDIRECT3DINDEXBUFFER9       ib;
	};

	struct Inst
	{
		uint meshInd;
		mat4 transform;
	};

	std::vector<Mesh> meshes;
	std::vector<Inst> instances;
};
