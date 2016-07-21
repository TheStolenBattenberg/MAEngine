#pragma once 

/**
 * Includes
 */

#include <MAE/Core/Types.h>

#include <d3d9.h>
#include <vector>
#include <MAE/Core/Mat.h>
#include <MPM.h>

class MPMModel {
public:
	MPMModel(class Renderer* renderer): renderer(renderer) { }
	~MPMModel();

	void load(const std::string& model);
	void render();

private:
	void readInstances(std::ifstream& f);
	void readMesh(std::ifstream& f);
	void readVertexDesc(std::ifstream& f);
	void readVertexData(std::ifstream& f);
	void readIndexData(std::ifstream& f);

	struct Mesh {
		uint matInd;

		uint numVertices;
		uint numPrim;

		uint stride;

		LPDIRECT3DVERTEXDECLARATION9 decl;
		LPDIRECT3DVERTEXBUFFER9      vb;
		LPDIRECT3DINDEXBUFFER9       ib;
	};

	struct Inst {
		uint meshInd;
		mat4 transform;
	};

	class Renderer* renderer;

	std::vector<Mesh> meshes;
	std::vector<Inst> instances;
};
