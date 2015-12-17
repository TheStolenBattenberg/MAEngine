#include "D3DExporter.h"

#include <assimp\scene.h>
#include <DefaultIOSystem.h>
#include <BaseImporter.h>

#include <sstream>

typedef unsigned int uint;

enum PrimitiveType
{
	PrimitiveNone          = 0,
	PrimitivePointList     = 1,
	PrimitiveLineList      = 2,
	PrimitiveTriangleList  = 4
};

enum VertexType
{
	VertexPosition                   = 2,
	VertexPositionColor              = 3,
	VertexPositionTexture            = 4,
	VertexPositionTextureColor       = 5,
	VertexPositionNormal             = 6,
	VertexPositionNormalColor        = 7,
	VertexPositionNormalTexture      = 8,
	VertexPositionNormalTextureColor = 9
};

struct D3DVertex
{
	PrimitiveType type;

	aiVector3D pos;
	aiVector3D norm;
	aiVector2D texCoord;
	uint       color;
};

void NodeToVertices(const aiScene* scene, const aiNode* node, const aiMatrix4x4& mat, std::vector<D3DVertex>& vertices);
VertexType GetTypeFromVertex(D3DVertex& vertex);

void D3DRegisterExporter(Assimp::Exporter& exp)
{
	Assimp::Exporter::ExportFormatEntry entry("d3d", "Game Maker 3D Format", "d3d", [](const char* file, Assimp::IOSystem* iohandler, const aiScene* scene, const Assimp::ExportProperties* prop)
	{
		Assimp::IOStream* f = iohandler->Open(file, "wb");

		if (f == 0)
			throw DeadlyExportError("Failed to open file");

		std::vector<D3DVertex> vertices;

		NodeToVertices(scene, scene->mRootNode, scene->mRootNode->mTransformation, vertices);

		PrimitiveType t = PrimitiveNone;

		uint lineCount = 0;

		for (auto i : vertices)
		{
			if (t != i.type)
			{
				if (t != PrimitiveNone)
					++lineCount;

				t = i.type;
				++lineCount;
			}

			++lineCount;
		}

		if (t != PrimitiveNone)
			++lineCount;

		std::stringstream ss;

		ss << "100\r\n"
		   << lineCount
		   << "\r\n";

		t = PrimitiveNone;

		for (auto i : vertices)
		{
			if (t != i.type)
			{
				if (t != PrimitiveNone)
					ss << "1 0 0 0 0 0 0 0 0 0 0\r\n";

				t = i.type;

				ss << "0 " << t << " 0 0 0 0 0 0 0 0 0\r\n";
			}

			VertexType type = GetTypeFromVertex(i);

			ss << std::fixed << type << ' ' << i.pos.x << ' ' << i.pos.y << ' ' << i.pos.z;

			if (type == VertexPositionNormal || type == VertexPositionNormalColor || type == VertexPositionNormalTexture || type == VertexPositionNormalTextureColor)
				ss << std::fixed << ' ' << i.norm.x << ' ' << i.norm.y << ' ' << i.norm.z;

			if (type == VertexPositionTexture || type == VertexPositionTextureColor || type == VertexPositionNormalTexture || type == VertexPositionNormalTextureColor)
				ss << std::fixed << ' ' << i.texCoord.x << ' ' << i.texCoord.y;

			if (type == VertexPositionColor || type == VertexPositionTextureColor || type == VertexPositionNormalColor || type == VertexPositionNormalTextureColor)
				ss << std::fixed << ' ' << (i.color & 0xFFFFFF) << ' ' << ((i.color >> 24) / 255.0f);

			switch (type)
			{
			case VertexPosition:
				ss << " 0 0 0 0 0 0 0\r\n";
				break;
			case VertexPositionTexture:
			case VertexPositionColor:
				ss << " 0 0 0 0 0\r\n";
				break;
			case VertexPositionTextureColor:
				ss << " 0 0 0\r\n";
				break;
			case VertexPositionNormal:
				ss << " 0 0 0 0\r\n";
				break;
			case VertexPositionNormalTexture:
			case VertexPositionNormalColor:
				ss << " 0 0\r\n";
				break;
			case VertexPositionNormalTextureColor:
				ss << "\r\n";
				break;
			}
		}

		if (t != PrimitiveNone)
			ss << "1 0 0 0 0 0 0 0 0 0 0\r\n";

		if (f->Write(ss.str().data(), 1, ss.str().length()) == 0)
			throw DeadlyExportError("Failed to write to file");

		iohandler->Close(f);
	});

	exp.RegisterExporter(entry);
}

void NodeToVertices(const aiScene* scene, const aiNode* node, const aiMatrix4x4& mat, std::vector<D3DVertex>& vertices)
{
	aiMatrix3x3 normMat = aiMatrix3x3(mat).Inverse().Transpose();

	for (uint i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* m = scene->mMeshes[i];

		for (uint j = 0; j < m->mNumFaces; ++j)
		{
			PrimitiveType t = PrimitiveNone;

			switch (m->mFaces[j].mNumIndices)
			{
			case 3:
				t = PrimitiveTriangleList;
				break;
			case 2:
				t = PrimitiveLineList;
				break;
			case 1:
				t = PrimitivePointList;
				break;
			}

			if (t == PrimitiveNone)
				continue;

			for (uint k = 0; k < m->mFaces[j].mNumIndices; ++k)
			{
				D3DVertex vert;

				vert.type = t;

				uint ind = m->mFaces[j].mIndices[k];

				if (m->HasPositions())
					vert.pos = mat * m->mVertices[ind];

				if (m->HasNormals())
					if (fpclassify(m->mNormals[ind].x) != FP_NAN &&
					    fpclassify(m->mNormals[ind].y) != FP_NAN &&
					    fpclassify(m->mNormals[ind].z) != FP_NAN)
						vert.norm = normMat * m->mNormals[ind];

				if (m->HasTextureCoords(0))
					vert.texCoord = aiVector2D(m->mTextureCoords[0][ind].x,
					                           m->mTextureCoords[0][ind].y);

				if (m->HasVertexColors(0))
					vert.color = (uint) (m->mColors[0][ind].a * 255.0f) << 24 |
					             (uint) (m->mColors[0][ind].b * 255.0f) << 16 |
					             (uint) (m->mColors[0][ind].g * 255.0f) << 8 |
					             (uint) (m->mColors[0][ind].r * 255.0f);
				else
					vert.color = 0xFFFFFFFF;

				vertices.push_back(vert);
			}
		}
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		NodeToVertices(scene, node->mChildren[i], mat * node->mChildren[i]->mTransformation, vertices);
}

VertexType GetTypeFromVertex(D3DVertex& vertex)
{
	bool hasNormal = vertex.norm != aiVector3D();
	bool hasTexCoord = vertex.texCoord != aiVector2D();
	bool hasColor = vertex.color != 0xFFFFFFFF;

	if (!hasNormal && !hasTexCoord && hasColor)
		return VertexPositionColor;

	if (!hasNormal && hasTexCoord && !hasColor)
		return VertexPositionTexture;

	if (!hasNormal && hasTexCoord && hasColor)
		return VertexPositionTextureColor;

	if (hasNormal && !hasTexCoord && !hasColor)
		return VertexPositionNormal;

	if (hasNormal && !hasTexCoord && hasColor)
		return VertexPositionNormalColor;

	if (hasNormal && hasTexCoord && !hasColor)
		return VertexPositionNormalTexture;

	if (hasNormal && hasTexCoord && hasColor)
		return VertexPositionNormalTextureColor;

	return VertexPosition;
}
