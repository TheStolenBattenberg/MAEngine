#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>

class GM3DImporter
{
public:
	GM3DImporter();

	bool importModel(const std::string& file);
	bool exportModel(const std::string& file);

	const char* getError();
	const aiScene* getScene();

	unsigned int ppf = 0;

private:
	const aiScene* scene = 0;
	const char* error = "";

	Assimp::Importer imp;
	Assimp::Exporter exp;
};
