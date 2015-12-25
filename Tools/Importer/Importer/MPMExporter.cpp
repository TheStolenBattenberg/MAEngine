#include "MPMExporter.h"

#include "ModelMPM.h"

#include <assimp/scene.h>
#include <DefaultIOSystem.h>
#include <BaseImporter.h>
#include <assimp/material.h>

#include <stack>

enum UsageFlags
{
	UsageFlagPosition   = 0x01,
	UsageFlagNormal     = 0x02,
	UsageFlagTexCoord   = 0x04,
	UsageFlagColor      = 0x08,
	UsageFlagBoneIndex  = 0x10,
	UsageFlagBoneWeight = 0x20
};

struct Vertex
{
	aiVector3D       pos;
	aiVector3D       norm;
	aiVector2D       texCoord;
	aiColor4t<ubyte> color;
};

struct Material
{
	col4u ambient;
	col4u diffuse;
	col4u emissive;
	col4u specular;
	float reflectivity;

	std::string tex;
	std::string shader;
	std::string environment;

	bool operator==(const Material& m)
	{
		return ambient      == m.ambient      &&
		       diffuse      == m.diffuse      &&
		       emissive     == m.emissive     &&
		       specular     == m.specular     &&
		       reflectivity == m.reflectivity &&
		       tex          == m.tex          &&
		       shader       == m.shader       &&
		       environment  == m.environment;
	}

	static Material defaultMaterial()
	{
		Material m = {col4u(0), col4u(), col4u(), col4u(), -1, "", "", ""};

		return m;
	}
};

struct Mesh
{
	uint matInd;

	uint vertFmt;

	uint numVert;
	uint numInd;

	void* data;
	void* indexData;
};

template<typename T> inline aiColor4t<T> ToColor4t(aiColor4D col, float mul = 1.0f)
{
	return aiColor4t<T>(T(col.a * mul), T(col.r * mul), T(col.g * mul), T(col.b * mul));
}

template<typename T> inline aiVector2t<T> ToVec2(aiVector3t<T> vec)
{
	return aiVector2t<T>(vec.x, vec.y);
}

template<typename T> inline col4u ToCol4u(aiColor4t<T> col, T mul = T(1))
{
	return col4u(ubyte(col.a * mul), ubyte(col.r * mul), ubyte(col.g * mul), ubyte(col.b * mul));
}

inline void WriteToFileRaw(Assimp::IOStream* f, const void* data, uint length)
{
	if (f->Write(data, length, 1) != 1)
		throw DeadlyExportError("Failed to write to file");
}

template<typename T> inline void WriteToFile(Assimp::IOStream* f, const T& val)
{
	WriteToFileRaw(f, &val, sizeof(val));
}

inline bool IsVec3Invalid(aiVector3D vec) {
	return std::fpclassify(vec.x) == FP_NAN ||
	       std::fpclassify(vec.x) == FP_NAN ||
	       std::fpclassify(vec.x) == FP_NAN;
}

void GenerateMeshes(const aiScene* scene, std::map<uint, std::tuple<uint, Mesh>>& meshes, std::vector<Material>& materials);
bool GenerateMesh(const aiMesh* mesh, Mesh& processedMesh);
uint GetNumVertices(const std::vector<Vertex>& vertices, uint vertFmt);
uint GetNumTris(const aiMesh* mesh);
uint GetNumComponents(uint usage);
uint GetSizeFromFormat(uint fmt);
uint GetUsedComponents(const std::vector<Vertex>& vertices, uint mask);
uint GetAvailableComponents(const aiMesh* mesh);
void BuildMesh(Mesh& data, const std::vector<Vertex>& vertices, uint fmt);
void BuildMeshIndexed(Mesh& data, const std::vector<Vertex>& vertices, uint fmt, uint numVerts);
void BuildVertexFromFormat(uint fmt, const Vertex& vert, void* out);
Material CreateMaterial(const aiMaterial* mat);
void MeshToVertices(const aiMesh* mesh, std::vector<Vertex>& vertices);
uint CountPackets(const std::vector<Mesh>& meshes);
void WriteMeshes(Assimp::IOStream* f, const std::map<uint, std::tuple<uint, Mesh>>& meshes, const std::vector<Material>& materials);
void WriteInstances(Assimp::IOStream* f, const aiScene* scene, const std::map<uint, std::tuple<uint, Mesh>>& meshes);
void WriteMaterials(Assimp::IOStream* f, const std::vector<Material>& materials);

void MPMRegisterExporter(Assimp::Exporter& exp)
{
	Assimp::Exporter::ExportFormatEntry entry("mpm", "MAE Packed Model", "mpm", [](const char* file, Assimp::IOSystem* iohandler, const aiScene* scene, const Assimp::ExportProperties* prop)
	{
		std::map<uint, std::tuple<uint, Mesh>>  meshes;
		std::vector<Material> materials;

		GenerateMeshes(scene, meshes, materials);

		Assimp::IOStream* f = iohandler->Open(file, "wb");

		if (f == 0)
			throw DeadlyExportError("Failed to open file");

		WriteToFile<MPMModel::Header>(f, {MPMModel::MagicNumber, MPMModel::Version, MPMModel::CompVersion, meshes.size(), materials.size()});

		WriteInstances(f, scene, meshes);
		WriteMaterials(f, materials);
		WriteMeshes(f, meshes, materials);

		WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketEndOfFileID, 0});

		iohandler->Close(f);
	});

	exp.RegisterExporter(entry);
}

bool GenerateMesh(const aiMesh* mesh, Mesh& processedMesh)
{
	/**
	 * Generate vertices from mesh
	 */

	std::vector<Vertex> vertices;

	MeshToVertices(mesh, vertices);

	if (vertices.size() == 0)
		return 0;

	/**
	 * Check which components are used
	 */

	processedMesh.vertFmt = GetUsedComponents(vertices, GetAvailableComponents(mesh));

	if ((processedMesh.vertFmt & UsageFlagPosition) == 0)
		return 0;

	/**
	 * Build mesh
	 */

	uint size = GetSizeFromFormat(processedMesh.vertFmt);
	uint numVerts = GetNumVertices(vertices, processedMesh.vertFmt);

	if (numVerts * size + vertices.size() * (numVerts > 0xFFFF ? sizeof(uint) : sizeof(ushort)) < vertices.size() * size)
		BuildMeshIndexed(processedMesh, vertices, processedMesh.vertFmt, numVerts);
	else
		BuildMesh(processedMesh, vertices, processedMesh.vertFmt);

	return 1;
}

uint GetNumVertices(const std::vector<Vertex>& vertices, uint vertFmt)
{
	uint numVerts = 0;

	for (uint i = 0; i < vertices.size(); ++i)
	{
		bool found = 0;

		for (uint j = 0; j < i; ++j)
		{
			if (vertFmt & UsageFlagPosition)
				if (!vertices[j].pos.Equal(vertices[i].pos))
					continue;

			if (vertFmt & UsageFlagNormal)
				if (!vertices[j].norm.Equal(vertices[i].norm))
					continue;

			if (vertFmt & UsageFlagTexCoord)
				if (!vertices[j].texCoord.Equal(vertices[i].texCoord))
					continue;

			if (vertFmt & UsageFlagColor)
				if (vertices[j].color != vertices[i].color)
					continue;

			found = 1;
			break;
		}

		if (!found)
			++numVerts;
	}

	return numVerts;
}

uint GetSizeFromFormat(uint fmt)
{
	return (fmt & UsageFlagPosition ? 12 : 0) + (fmt & UsageFlagNormal ? 12 : 0) + (fmt & UsageFlagTexCoord ? 8 : 0) + (fmt & UsageFlagColor ? 4 : 0);
}

uint GetNumTris(const aiMesh* mesh)
{
	uint tris = 0;

	for (uint i = 0; i < mesh->mNumFaces; ++i)
		if (mesh->mFaces->mNumIndices == 3)
			++tris;

	return tris;
}

void BuildMesh(Mesh& data, const std::vector<Vertex>& vertices, uint fmt)
{
	uint size = GetSizeFromFormat(fmt);
	data.data = new ubyte[size * vertices.size()];

	data.indexData = 0;

	for (uint i = 0; i < vertices.size(); ++i)
		BuildVertexFromFormat(fmt, vertices[i], (ubyte*) data.data + i * size);

	data.numVert = vertices.size();
	data.numInd  = 0;
}

void BuildMeshIndexed(Mesh& data, const std::vector<Vertex>& vertices, uint fmt, uint numVerts)
{
	uint size = GetSizeFromFormat(fmt);
	void* tempData = new ubyte[size];

	data.data      = new ubyte[numVerts * size];
	data.indexData = new ubyte[vertices.size() * (numVerts > 0xFFFF ? sizeof(uint) : sizeof(ushort))];

	uint nextVert = 0;

	for (uint i = 0; i < vertices.size(); ++i)
	{
		BuildVertexFromFormat(fmt, vertices[i], tempData);

		uint j;

		for (j = 0; j < nextVert; ++j)
			if (memcmp(tempData, (ubyte*) data.data + j * size, size) == 0)
				break;

		if (j >= nextVert)
			memcpy((ubyte*) data.data + (j = nextVert++) * size, tempData, size);

		if (numVerts > 0xFFFF)
			((uint*) data.indexData)[i] = j;
		else
			((ushort*) data.indexData)[i] = j;
	}

	data.numVert = numVerts;
	data.numInd  = vertices.size();

	delete[] tempData;
}

void BuildVertexFromFormat(uint fmt, const Vertex& vert, void* out)
{
	if (fmt & UsageFlagPosition)
	{
		((float*) out)[0] = vert.pos.x;
		((float*) out)[1] = vert.pos.y;
		((float*) out)[2] = vert.pos.z;

		out = (ubyte*) out + 12;
	}

	if (fmt & UsageFlagNormal)
	{
		((float*) out)[0] = vert.norm.x;
		((float*) out)[1] = vert.norm.y;
		((float*) out)[2] = vert.norm.z;

		out = (ubyte*) out + 12;
	}

	if (fmt & UsageFlagTexCoord)
	{
		((float*) out)[0] = vert.texCoord.x;
		((float*) out)[1] = vert.texCoord.y;

		out = (ubyte*) out + 8;
	}

	if (fmt & UsageFlagColor)
	{
		((col4u*) out)[0] = ToCol4u(vert.color);

		out = (ubyte*) out + 4;
	}
}

Material CreateMaterial(const aiMaterial* mat)
{
	Material ret = Material::defaultMaterial();

	aiColor4D col;

	if (mat->Get(AI_MATKEY_COLOR_AMBIENT, col) == AI_SUCCESS)
		ret.ambient = ToCol4u(col, 255.0f);

	if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, col) == AI_SUCCESS)
		ret.diffuse = ToCol4u(col, 255.0f);

	if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, col) == AI_SUCCESS)
		ret.emissive = ToCol4u(col, 255.0f);

	if (mat->Get(AI_MATKEY_COLOR_SPECULAR, col) == AI_SUCCESS)
		ret.specular = ToCol4u(col, 255.0f);

	if (mat->Get(AI_MATKEY_COLOR_REFLECTIVE, ret.reflectivity) != AI_SUCCESS)
		ret.reflectivity = -1;
	else if (ret.reflectivity <= 0)
		ret.reflectivity = -1;

	aiString str;

	if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS)
			ret.tex = str.C_Str();

	return ret;
}

void MeshToVertices(const aiMesh* mesh, std::vector<Vertex>& vertices)
{
	/**
	 * Assume each face is a triangle
	 */

	vertices.reserve(3 * mesh->mNumFaces);

	for (uint i = 0; i < mesh->mNumFaces; ++i)
	{
		if (mesh->mFaces[i].mNumIndices != 3)
			continue;

		for (uint j = 0; j < 3; ++j)
		{
			uint ind = mesh->mFaces[i].mIndices[j];

			Vertex v;

			if (mesh->HasPositions())
				v.pos = mesh->mVertices[ind];
			else
				v.pos = aiVector3D();

			if (mesh->HasNormals())
				v.norm = IsVec3Invalid(mesh->mNormals[ind]) ? aiVector3D() : mesh->mNormals[ind];
			else
				v.norm = aiVector3D();

			if (mesh->HasTextureCoords(0))
				v.texCoord = ToVec2(mesh->mTextureCoords[0][ind]);
			else
				v.texCoord = aiVector2D();

			if (mesh->HasVertexColors(0))
				v.color = ToColor4t<ubyte>(mesh->mColors[0][ind], 255);
			else
				v.color = aiColor4t<ubyte>();

			vertices.push_back(v);
		}
	}
}

uint GetUsedComponents(const std::vector<Vertex>& vertices, uint mask)
{
	uint fmt = 0;

	if (mask & UsageFlagPosition)
	{
		uint i;

		for (i = 0; i < vertices.size(); ++i)
			if (vertices[i].pos != aiVector3D())
				break;

		if (i < vertices.size())
			fmt |= UsageFlagPosition;
	}

	if (mask & UsageFlagNormal)
	{
		uint i;

		for (i = 0; i < vertices.size(); ++i)
			if (vertices[i].norm != aiVector3D())
				break;

		if (i < vertices.size())
			fmt |= UsageFlagNormal;
	}

	if (mask & UsageFlagTexCoord)
	{
		uint i;

		for (i = 0; i < vertices.size(); ++i)
			if (vertices[i].texCoord != aiVector2D())
				break;

		if (i < vertices.size())
			fmt |= UsageFlagTexCoord;
	}

	if (mask & UsageFlagColor)
	{
		uint i;

		for (i = 0; i < vertices.size(); ++i)
			if (vertices[i].color != aiColor4t<ubyte>(255))
				break;

		if (i < vertices.size())
			fmt |= UsageFlagColor;
	}

	return fmt;
}

uint GetAvailableComponents(const aiMesh* mesh)
{
	return (mesh->HasPositions()      ? UsageFlagPosition : 0) |
	       (mesh->HasNormals()        ? UsageFlagNormal   : 0) |
	       (mesh->HasTextureCoords(0) ? UsageFlagTexCoord : 0) |
	       (mesh->HasVertexColors(0)  ? UsageFlagColor    : 0);
}

void GenerateMeshes(const aiScene* scene, std::map<uint, std::tuple<uint, Mesh>>& meshes, std::vector<Material>& materials)
{
	materials.reserve(scene->mNumMaterials);

	Mesh mesh;

	for (uint i = 0; i < scene->mNumMeshes; ++i)
	{
		if (GenerateMesh(scene->mMeshes[i], mesh))
		{
			Material m = scene->HasMaterials() ? CreateMaterial(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]) : Material::defaultMaterial();

			auto ind = std::find(materials.begin(), materials.end(), m);

			if (ind == materials.end())
			{
				mesh.matInd = materials.size();
				materials.push_back(m);
			}
			else
				mesh.matInd = ind - materials.begin();

			meshes[i] = std::tuple<uint, Mesh>(meshes.size(), mesh);
		}
	}
}

void WriteMeshes(Assimp::IOStream* f, const std::map<uint, std::tuple<uint, Mesh>>& meshes, const std::vector<Material>& materials)
{
	for (auto i : meshes)
	{
		uint ind = std::get<0>(i.second);
		Mesh& mesh = std::get<1>(i.second);

		WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketMeshID, sizeof(MPMModel::Mesh)});
		WriteToFile<MPMModel::Mesh>(f, {ind, mesh.matInd, mesh.numVert, mesh.numInd});

		uint num  = GetNumComponents(mesh.vertFmt);
		uint size = GetSizeFromFormat(mesh.vertFmt);

		WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketVertexDescID, sizeof(MPMModel::PacketVertexDescHeader) + num * sizeof(MPMModel::PacketVertexDesc)});
		WriteToFile<MPMModel::PacketVertexDescHeader>(f, {ind, num, size, 0});
		
		ushort ofs = 0;

		if (mesh.vertFmt & UsageFlagPosition)
		{
			WriteToFile<MPMModel::PacketVertexDesc>(f, {0, MPMModel::PacketVertexDesc::UsagePosition, MPMModel::PacketVertexDesc::TypeVec3, ofs});
			ofs += 12;
		}

		if (mesh.vertFmt & UsageFlagNormal)
		{
			WriteToFile<MPMModel::PacketVertexDesc>(f, {0, MPMModel::PacketVertexDesc::UsageNormal, MPMModel::PacketVertexDesc::TypeVec3, ofs});
			ofs += 12;
		}

		if (mesh.vertFmt & UsageFlagTexCoord)
		{
			WriteToFile<MPMModel::PacketVertexDesc>(f, {0, MPMModel::PacketVertexDesc::UsageTexCoord, MPMModel::PacketVertexDesc::TypeVec2, ofs});
			ofs += 8;
		}

		if (mesh.vertFmt & UsageFlagColor)
		{
			WriteToFile<MPMModel::PacketVertexDesc>(f, {0, MPMModel::PacketVertexDesc::UsageColor, MPMModel::PacketVertexDesc::TypeColor, ofs});
			ofs += 4;
		}

		WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketVertexDataID, sizeof(MPMModel::PacketVertexDataHeader) + mesh.numVert * size});
		WriteToFile<MPMModel::PacketVertexDataHeader>(f, {ind, mesh.numVert * size});
		WriteToFileRaw(f, mesh.data, mesh.numVert * size);

		if (mesh.numInd != 0)
		{
			uint indSize = mesh.numInd > 0xFFFF ? sizeof(uint) : sizeof(ushort);

			WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketVertexIndexDataID, sizeof(MPMModel::PacketVertexIndexHeader) + mesh.numInd * indSize});
			WriteToFile<MPMModel::PacketVertexIndexHeader>(f, {ind, mesh.numInd, (uint) (mesh.numInd > 0xFFFF ? MPMModel::PacketVertexIndexHeader::TypeU32 : MPMModel::PacketVertexIndexHeader::TypeU16)});
			WriteToFileRaw(f, mesh.indexData, mesh.numInd * indSize);
		}
	}
}

void WriteInstances(Assimp::IOStream* f, const aiScene* scene, const std::map<uint, std::tuple<uint, Mesh>>& meshes)
{
	std::stack<std::tuple<aiNode*, aiMatrix4x4>> stack;
	stack.push(std::tuple<aiNode*, aiMatrix4x4>(scene->mRootNode, scene->mRootNode->mTransformation));

	std::vector<MPMModel::Inst> instances;

	while (!stack.empty())
	{
		aiNode* node    = std::get<0>(stack.top());
		aiMatrix4x4 mat = std::get<1>(stack.top());

		stack.pop();

		aiVector3D   scaling;
		aiQuaternion rotation;
		aiVector3D   translation;

		mat.Decompose(scaling, rotation, translation);

		for (uint i = 0; i < node->mNumMeshes; ++i)
		{
			auto ind = meshes.find(node->mMeshes[i]);

			if (ind != meshes.end())
			{
				instances.push_back({
					std::get<0>(*ind),
					vec3(translation.x, translation.y, translation.z),
					vec3(scaling.x, scaling.y, scaling.z),
					quat(rotation.x, rotation.y, rotation.z, rotation.w)
				});
			}
		}

		for (uint i = 0; i < node->mNumChildren; ++i)
			stack.push(std::tuple<aiNode*, aiMatrix4x4>(node->mChildren[i], mat * node->mChildren[i]->mTransformation));
	}

	WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketInstID, sizeof(MPMModel::InstHeader) + instances.size() * sizeof(MPMModel::Inst)});
	WriteToFile<MPMModel::InstHeader>(f, {instances.size()});

	for (auto i : instances)
		WriteToFile(f, i);
}

void WriteMaterials(Assimp::IOStream* f, const std::vector<Material>& materials)
{
	WriteToFile<MPMModel::PacketHeader>(f, {MPMModel::PacketMaterialID, sizeof(MPMModel::MaterialHeader) + materials.size() * sizeof(MPMModel::Material)});
	WriteToFile<MPMModel::MaterialHeader>(f, {materials.size()});

	for (auto i : materials)
	{
		MPMModel::Material mat;

		mat.ambient      = i.ambient;
		mat.diffuse      = i.diffuse;
		mat.emissive     = i.emissive;
		mat.specular     = i.specular;
		mat.reflectivity = i.reflectivity;
		
		memset(mat.tex, 0, sizeof(mat.tex));
		memset(mat.shader, 0, sizeof(mat.shader));
		memset(mat.environment, 0, sizeof(mat.environment));

		memcpy(mat.tex, i.tex.c_str(), std::min(sizeof(mat.tex), i.tex.size()));
		memcpy(mat.shader, i.shader.c_str(), std::min(sizeof(mat.shader), i.shader.size()));
		memcpy(mat.environment, i.environment.c_str(), std::min(sizeof(mat.environment), i.environment.size()));

		WriteToFile(f, mat);
	}
}

uint GetNumComponents(uint usage)
{
	return (usage & UsageFlagPosition ? 1 : 0) +
	       (usage & UsageFlagNormal   ? 1 : 0) +
	       (usage & UsageFlagTexCoord ? 1 : 0) +
	       (usage & UsageFlagColor    ? 1 : 0);
}
