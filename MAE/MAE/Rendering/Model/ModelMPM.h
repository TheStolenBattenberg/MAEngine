#pragma once

#include <MPM.h>
#include <MAE/Rendering/Model/ModelDraft.h>

#include <fstream>

class MPMModel {
public:
	static inline class ModelDraft* load(const std::string& file) {
		return load(file.c_str());
	}

	static class ModelDraft* load(const char* file);
	
private:
	static void readInstances(class DynamicArray<ModelDraft::Inst>& inst, std::ifstream& f);
	static void readMaterials(class DynamicArray<ModelDraft::Material>& materials, std::ifstream& f);
	static void readMesh(class DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f);
	static void readVertexDesc(class DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f);
	static void readVertexData(class DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f);
	static void readIndexData(class DynamicArray<ModelDraft::Mesh>& meshes, std::ifstream& f);
};
