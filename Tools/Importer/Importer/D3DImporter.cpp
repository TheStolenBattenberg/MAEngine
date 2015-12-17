#include "D3DImporter.h"

#include "parser.h"

#include <assimp\scene.h>
#include <DefaultIOSystem.h>
#include <BaseImporter.h>

#include <sstream>
#include <string>
#include <vector>

#include <math.h>

#define M_PIF    3.14159265359f
#define M_DBLPIF 6.28318530718f

typedef unsigned int uint;

aiImporterDesc desc =
{
	"Game Maker D3D Importer",
	"", "", "",
	aiImporterFlags_SupportTextFlavour,
	100, 0, 100, 0,
	"d3d mod gmmod"
};

enum PrimitiveType
{
	PrimitiveNone          = 0,
	PrimitivePointList     = 1,
	PrimitiveLineList      = 2,
	PrimitiveLineStrip     = 3,
	PrimitiveTriangleList  = 4,
	PrimitiveTriangleStrip = 5,
	PrimitiveTriangleFan   = 6
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

/**
 * Switched to class because compiler magicaly skipped bytes
 */

class D3DVertex
{
public:
	PrimitiveType type;

	aiVector3D pos;
	aiVector3D norm;
	aiVector2D texCoord;
	aiColor4D  color;
};

class GMD3DLoader: public Assimp::BaseImporter
{
public:
	bool CanRead(const std::string& pFile, Assimp::IOSystem* pIOHandler, bool checkSig) const;

private:
	const aiImporterDesc* GetInfo() const;
	void InternReadFile(const std::string& pFile, aiScene* pScene, Assimp::IOSystem* pIOHandler);
};

void ProcessVertices(std::vector<D3DVertex>& out, std::vector<D3DVertex>& in, PrimitiveType pr);
void GenerateMesh(std::vector<D3DVertex>& vertices, aiMesh* mesh);
uint CountFaces(std::vector<D3DVertex>& vertices, uint* prTypes = 0);
bool HasNormals(std::vector<D3DVertex>& vertices);
bool HasTexCoords(std::vector<D3DVertex>& vertices);
bool HasColors(std::vector<D3DVertex>& vertices);

bool GMD3DLoader::CanRead(const std::string& pFile, Assimp::IOSystem* pIOHandler, bool checkSig) const
{
	if (checkSig)
		return 0;

	return SimpleExtensionCheck(pFile, "d3d", "mod", "gmmod");
}

const aiImporterDesc* GMD3DLoader::GetInfo() const
{
	return &desc;
}

void GMD3DLoader::InternReadFile(const std::string& pFile, aiScene* pScene, Assimp::IOSystem* pIOHandler)
{
	Assimp::IOStream* f = pIOHandler->Open(pFile);

	if (f == 0)
		throw DeadlyImportError("Failed to open file " + pFile + ".");

	std::vector<char> file;

	TextFileToBuffer(f, file);

	pIOHandler->Close(f);

	Parser p(file);

	/**
	 * Load header data
	 */

	double n;

	if (!p.readDouble(n) || (uint) n != 100)
		throw DeadlyImportError("Invalid file");

	p.skipLine();

	if (!p.readDouble(n))
		throw DeadlyImportError("Failed to read from file");

	uint lines = (uint) n;

	p.skipLine();

	std::vector<D3DVertex> processedVertices;
	std::vector<D3DVertex> vertices;

	PrimitiveType pr = PrimitiveNone;

	/**
	 * Process lines
	 */

	for (uint i = 0; i < lines; ++i)
	{
		float values[11];

		for (uint j = 0; j < sizeof(values) / sizeof(*values); ++j)
			if (!p.readFloat(values[j]))
				throw DeadlyImportError("Failed to read from file");

		p.skipLine();

		D3DVertex v = {PrimitiveNone, aiVector3D(), aiVector3D(), aiVector2D(), aiColor4D(1.0f)};

		uint color;

		float xx, yy, zz;
		float rx, ry, rz;
		float ss;

		switch ((uint) values[0])
		{
		case 0:
			if (pr != PrimitiveNone)
				ProcessVertices(processedVertices, vertices, pr);

			vertices.clear();

			pr = (PrimitiveType) (uint) values[1];
			break;
		case 1:
			ProcessVertices(processedVertices, vertices, pr);
			vertices.clear();

			pr = PrimitiveNone;
			break;
		case 2:
			v.pos = aiVector3D(values[1], values[2], values[3]);

			vertices.push_back(v);
			break;
		case 3:
			v.pos = aiVector3D(values[1], values[2], values[3]);

			color = (uint) values[4];
			v.color = aiColor4D((color & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, values[5]);

			vertices.push_back(v);
			break;
		case 4:
			v.pos      = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(values[4], values[5]);

			vertices.push_back(v);
			break;
		case 5:
			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(values[4], values[5]);
			
			color = (uint) values[6];
			v.color = aiColor4D((color & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, values[7]);

			vertices.push_back(v);
			break;
		case 6:
			v.pos  = aiVector3D(values[1], values[2], values[3]);
			v.norm = aiVector3D(values[4], values[5], values[6]);

			vertices.push_back(v);
			break;
		case 7:
			v.pos  = aiVector3D(values[1], values[2], values[3]);
			v.norm = aiVector3D(values[4], values[5], values[6]);

			color = (uint) values[7];
			v.color = aiColor4D((color & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, values[8]);

			vertices.push_back(v);
			break;
		case 8:
			v.pos      = aiVector3D(values[1], values[2], values[3]);
			v.norm     = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);

			vertices.push_back(v);
			break;
		case 9:
			v.pos      = aiVector3D(values[1], values[2], values[3]);
			v.norm     = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);

			color = (uint) values[9];
			v.color = aiColor4D((color & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, values[10]);

			vertices.push_back(v);
			break;
		case 10:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}
			
			/**
			 * Top
			 */

			v.norm = aiVector3D(0, 0, 1);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			/**
			 * Bottom
			 */

			v.norm = aiVector3D(0, 0, -1);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[3]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			/**
			 * Front
			 */

			v.norm = aiVector3D(0, 1, 0);

			v.pos = aiVector3D(values[1], values[5], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			/**
			* Back
			*/

			v.norm = aiVector3D(0, -1, 0);

			v.pos = aiVector3D(values[4], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			/**
			* Left
			*/

			v.norm = aiVector3D(1, 0, 0);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			/**
			* Right
			*/

			v.norm = aiVector3D(-1, 0, 0);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		case 11:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}

			xx = (values[4] + values[1]) / 2.0f;
			yy = (values[5] + values[2]) / 2.0f;
			rx = (values[4] - values[1]) / 2.0f;
			ry = (values[5] - values[2]) / 2.0f;

			for (float i = 0; i < values[10]; ++i)
			{
				float is0 = i / values[10];
				float is1 = (i + 1) / values[10];

				float ci0 = cosf(M_DBLPIF * is0);
				float si0 = sinf(M_DBLPIF * is0);
				float ci1 = cosf(M_DBLPIF * is1);
				float si1 = sinf(M_DBLPIF * is1);

				v.norm = aiVector3D(ci0, si0, 0);
				v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[3]);
				v.texCoord = aiVector2D(values[7] * is0, 0);
				vertices.push_back(v);

				v.norm = aiVector3D(ci1, si1, 0);
				v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[3]);
				v.texCoord = aiVector2D(values[7] * is1, 0);
				vertices.push_back(v);

				v.norm = aiVector3D(ci1, si1, 0);
				v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[6]);
				v.texCoord = aiVector2D(values[7] * is1, values[8]);
				vertices.push_back(v);

				v.norm = aiVector3D(ci1, si1, 0);
				v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[6]);
				v.texCoord = aiVector2D(values[7] * is1, values[8]);
				vertices.push_back(v);

				v.norm = aiVector3D(ci0, si0, 0);
				v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[6]);
				v.texCoord = aiVector2D(values[7] * is0, values[8]);
				vertices.push_back(v);

				v.norm = aiVector3D(ci0, si0, 0);
				v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[3]);
				v.texCoord = aiVector2D(values[7] * is0, 0);
				vertices.push_back(v);

				if (values[9] >= 0.5f)
				{
					v.norm = aiVector3D(0, 0, -1);

					v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[3]);
					v.texCoord = aiVector2D(values[7] * is0, 0);
					vertices.push_back(v);

					v.pos = aiVector3D(xx, yy, values[3]);
					v.texCoord = aiVector2D(values[7] * (i + 0.5f) / values[10], 0);
					vertices.push_back(v);

					v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[3]);
					v.texCoord = aiVector2D(values[7] * is1, 0);
					vertices.push_back(v);

					v.norm = aiVector3D(0, 0, 1);

					v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[6]);
					v.texCoord = aiVector2D(values[7] * is1, values[8]);
					vertices.push_back(v);

					v.pos = aiVector3D(xx, yy, values[6]);
					v.texCoord = aiVector2D(values[7] * (i + 0.5f) / values[10], values[8]);
					vertices.push_back(v);

					v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[6]);
					v.texCoord = aiVector2D(values[7] * is0, values[8]);
					vertices.push_back(v);
				}
			}

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		case 12:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}

			xx = (values[4] + values[1]) / 2.0f;
			yy = (values[5] + values[2]) / 2.0f;
			rx = (values[4] - values[1]) / 2.0f;
			ry = (values[5] - values[2]) / 2.0f;

			for (float i = 0; i < values[10]; ++i)
			{
				float is0 = i / values[10];
				float is5 = (i + 0.5f) / values[10];
				float is1 = (i + 1.0f) / values[10];

				float ci0 = cosf(M_DBLPIF * is0);
				float si0 = sinf(M_DBLPIF * is0);
				float ci5 = cosf(M_DBLPIF * is5);
				float si5 = sinf(M_DBLPIF * is5);
				float ci1 = cosf(M_DBLPIF * is1);
				float si1 = sinf(M_DBLPIF * is1);

				aiVector2D norm;

				norm = aiVector2D(values[6] - values[3], aiVector2D(rx * ci0, ry * si0).Length()).Normalize();

				v.norm = aiVector3D(norm.x * ci0, norm.x * si0, norm.y);
				v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[3]);
				v.texCoord = aiVector2D(values[7] * is0, 0);
				vertices.push_back(v);

				norm = aiVector2D(values[6] - values[3], aiVector2D(rx * ci1, ry * si1).Length()).Normalize();

				v.norm = aiVector3D(norm.x * ci1, norm.x * si1, norm.y);
				v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[3]);
				v.texCoord = aiVector2D(values[7] * is1, 0);
				vertices.push_back(v);

				norm = aiVector2D(values[6] - values[3], aiVector2D(rx * ci5, ry * si5).Length()).Normalize();

				v.norm = aiVector3D(norm.x * ci5, norm.x * si5, norm.y);
				v.pos = aiVector3D(xx, yy, values[6]);
				v.texCoord = aiVector2D(values[7] * is5, values[8]);
				vertices.push_back(v);

				if (values[9] >= 0.5f)
				{
					v.norm = aiVector3D(0, 0, -1);

					v.pos = aiVector3D(xx + rx * ci0, yy + ry * si0, values[3]);
					v.texCoord = aiVector2D(values[7] * is0, 0);
					vertices.push_back(v);

					v.pos = aiVector3D(xx, yy, values[3]);
					v.texCoord = aiVector2D(values[7] * is5, 0);
					vertices.push_back(v);

					v.pos = aiVector3D(xx + rx * ci1, yy + ry * si1, values[3]);
					v.texCoord = aiVector2D(values[7] * is1, 0);
					vertices.push_back(v);
				}
			}

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		case 13:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}

			xx = (values[4] + values[1]) / 2.0f;
			yy = (values[5] + values[2]) / 2.0f;
			zz = (values[6] + values[3]) / 2.0f;
			rx = (values[4] - values[1]) / 2.0f;
			ry = (values[5] - values[2]) / 2.0f;
			rz = (values[6] - values[3]) / 2.0f;
			ss = ceilf(values[9] / 2.0f);

			for (float i = 0; i < values[9]; ++i)
			{
				for (float j = 1; j < ss; ++j)
				{
					float is0 = i / values[9];
					float is1 = (i + 1) / values[9];
					float js0 = j / ss;
					float js1 = (j + 1) / ss;
					float jm1 = (j - 1) / ss;

					float ci0 = cosf(M_DBLPIF * is0);
					float si0 = sinf(M_DBLPIF * is0);
					float ci1 = cosf(M_DBLPIF * is1);
					float si1 = sinf(M_DBLPIF * is1);

					float cj0 = cosf(M_PIF * js0);
					float sj0 = sinf(M_PIF * js0);
					float cj1 = cosf(M_PIF * js1);
					float sj1 = sinf(M_PIF * js1);
					float cm1 = cosf(M_PIF * jm1);
					float sm1 = sinf(M_PIF * jm1);

					v.norm = aiVector3D(rx * ci0 * sj0, ry * si0 * sj0, -rz * cj0).Normalize();
					v.pos = aiVector3D(xx + rx * ci0 * sj0, yy + ry * si0 * sj0, zz - rz * cj0);
					v.texCoord = aiVector2D(values[7] * is0, 1 - js0);
					vertices.push_back(v);

					v.norm = aiVector3D(rx * ci1 * sj0, ry * si1 * sj0, -rz * cj0).Normalize();
					v.pos = aiVector3D(xx + rx * ci1 * sj0, yy + ry * si1 * sj0, zz - rz * cj0);
					v.texCoord = aiVector2D(values[7] * is1, 1 - js0);
					vertices.push_back(v);

					v.norm = aiVector3D(rx * ci1 * sj1, ry * si1 * sj1, -rz * cj1).Normalize();
					v.pos = aiVector3D(xx + rx * ci1 * sj1, yy + ry * si1 * sj1, zz - rz * cj1);
					v.texCoord = aiVector2D(values[7] * is1, 1 - js1);
					vertices.push_back(v);

					v.norm = aiVector3D(rx * ci1 * sj0, ry * si1 * sj0, -rz * cj0).Normalize();
					v.pos = aiVector3D(xx + rx * ci1 * sj0, yy + ry * si1 * sj0, zz - rz * cj0);
					v.texCoord = aiVector2D(values[7] * is1, 1 - js0);
					vertices.push_back(v);

					v.norm = aiVector3D(rx * ci0 * sj0, ry * si0 * sj0, -rz * cj0).Normalize();
					v.pos = aiVector3D(xx + rx * ci0 * sj0, yy + ry * si0 * sj0, zz - rz * cj0);
					v.texCoord = aiVector2D(values[7] * is0, 1 - js0);
					vertices.push_back(v);

					v.norm = aiVector3D(rx * ci0 * sm1, ry * si0 * sm1, -rz * cm1).Normalize();
					v.pos = aiVector3D(xx + rx * ci0 * sm1, yy + ry * si0 * sm1, zz - rz * cm1);
					v.texCoord = aiVector2D(values[7] * is0, 1 - jm1);
					vertices.push_back(v);
				}
			}

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		case 14:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}

			v.norm = (aiVector3D(values[1] - values[4], values[2] - values[5], 0) ^
			          aiVector3D(values[1] - values[4], values[2] - values[5], values[3] - values[6])).Normalize();

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[3]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[6]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		case 15:

			if (pr != PrimitiveNone)
			{
				ProcessVertices(processedVertices, vertices, pr);
				pr = PrimitiveNone;
				vertices.clear();
			}

			v.norm = (aiVector3D(0, values[2] - values[5], 0) ^ aiVector3D(values[1] - values[4], values[2] - values[5], values[3] - values[6])).Normalize();

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[5], values[3]);
			v.texCoord = aiVector2D(0, values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[5], values[6]);
			v.texCoord = aiVector2D(values[7], values[8]);
			vertices.push_back(v);

			v.pos = aiVector3D(values[4], values[2], values[6]);
			v.texCoord = aiVector2D(values[7], 0);
			vertices.push_back(v);

			v.pos = aiVector3D(values[1], values[2], values[3]);
			v.texCoord = aiVector2D(0, 0);
			vertices.push_back(v);

			ProcessVertices(processedVertices, vertices, PrimitiveTriangleList);
			vertices.clear();

			break;
		}
	}

	if (pr != PrimitiveNone)
		ProcessVertices(processedVertices, vertices, pr);

	pScene->mMaterials = new aiMaterial*[1];
	pScene->mMaterials[0] = new aiMaterial();
	pScene->mNumMaterials = 1;

	pScene->mMeshes = new aiMesh*[1];
	pScene->mMeshes[0] = new aiMesh();
	pScene->mNumMeshes = 1;

	GenerateMesh(processedVertices, pScene->mMeshes[0]);

	pScene->mRootNode = new aiNode();

	pScene->mRootNode->mNumMeshes = 1;
	pScene->mRootNode->mMeshes    = new unsigned int;
	*pScene->mRootNode->mMeshes   = 0;
}

void ProcessVertices(std::vector<D3DVertex>& out, std::vector<D3DVertex>& in, PrimitiveType pr)
{
	uint v;

	switch (pr)
	{
	case PrimitivePointList:
		out.reserve(in.size());

		for (auto i: in)
			out.push_back(i);

		break;
	case PrimitiveLineList:
		v = (in.size() / 2) * 2;

		out.reserve(v);

		for (uint i = 0; i < v; ++i)
		{
			D3DVertex vert = in[i];
			vert.type = PrimitiveLineList;
			out.push_back(vert);
		}

		break;
	case PrimitiveLineStrip:
		if (in.size() < 2)
			return;

		out.reserve((in.size() - 1) * 2);

		for (uint i = 1; i < in.size(); ++i)
		{
			D3DVertex vert = in[i - 1];
			vert.type = PrimitiveLineList;
			
			out.push_back(vert);
			
			vert = in[i];
			vert.type = PrimitiveLineList;

			out.push_back(vert);
		}

		break;
	case PrimitiveTriangleList:
		v = (in.size() / 3) * 3;

		out.reserve(v);

		for (uint i = 0; i < v; ++i)
		{
			D3DVertex vert = in[i];
			vert.type = PrimitiveTriangleList;
			out.push_back(vert);
		}

		break;
	case PrimitiveTriangleStrip:
		if (in.size() < 3)
			return;

		out.reserve((in.size() - 2) * 3);

		for (uint i = 2; i < in.size(); ++i)
		{
			D3DVertex vert = in[i - 2];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);
			
			vert = in[i - 1];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);

			vert = in[i];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);
		}

		break;
	case PrimitiveTriangleFan:
		if (in.size() < 3)
			return;

		out.reserve((in.size() - 2) * 3);

		for (uint i = 2; i < in.size(); ++i)
		{
			D3DVertex vert = in[0];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);

			vert = in[i - 1];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);

			vert = in[i];
			vert.type = PrimitiveTriangleList;

			out.push_back(vert);
		}

		break;
	}
}

void GenerateMesh(std::vector<D3DVertex>& vertices, aiMesh* m)
{
	uint faces = CountFaces(vertices, &m->mPrimitiveTypes);

	if (vertices.size() != 0)
		m->mFaces = new aiFace[faces];

	uint ind = 0;

	for (uint i = 0; i < faces; ++i)
	{
		switch (vertices[ind].type)
		{
		case PrimitivePointList:
			m->mFaces[i].mIndices    = new uint[1];
			m->mFaces[i].mNumIndices = 1;
			m->mFaces[i].mIndices[0] = ind++;
			break;
		case PrimitiveLineList:
			m->mFaces[i].mIndices    = new uint[2];
			m->mFaces[i].mNumIndices = 2;
			m->mFaces[i].mIndices[0] = ind++;
			m->mFaces[i].mIndices[1] = ind++;
			break;
		case PrimitiveTriangleList:
			m->mFaces[i].mIndices    = new uint[3];
			m->mFaces[i].mNumIndices = 3;
			m->mFaces[i].mIndices[0] = ind++;
			m->mFaces[i].mIndices[1] = ind++;
			m->mFaces[i].mIndices[2] = ind++;
			break;
		}
	}

	m->mNumFaces = faces;

	if (vertices.size() != 0)
		m->mVertices = new aiVector3D[vertices.size()];

	m->mNumVertices = vertices.size();

	for (uint i = 0; i < vertices.size(); ++i)
		m->mVertices[i] = vertices[i].pos;

	if (HasNormals(vertices))
	{
		if (vertices.size() != 0)
			m->mNormals = new aiVector3D[vertices.size()];

		for (uint i = 0; i < vertices.size(); ++i)
			if (vertices[i].type == PrimitiveTriangleList)
				m->mNormals[i] = vertices[i].norm;
			else
				m->mNormals[i] = aiVector3D(std::nanf(""));
	}

	if (HasTexCoords(vertices))
	{
		if (vertices.size() != 0)
			m->mTextureCoords[0] = new aiVector3D[vertices.size()];

		m->mNumUVComponents[0] = 2;

		for (uint i = 0; i < vertices.size(); ++i)
			m->mTextureCoords[0][i] = aiVector3D(vertices[i].texCoord.x, vertices[i].texCoord.y, 0.0f);
	}

	if (HasColors(vertices))
	{
		if (vertices.size() != 0)
			m->mColors[0] = new aiColor4D[vertices.size()];

		for (uint i = 0; i < vertices.size(); ++i)
			m->mColors[0][i] = vertices[i].color;
	}
}

uint CountFaces(std::vector<D3DVertex>& vertices, uint* prTypes)
{
	uint faces = 0;

	for (uint i = 0; i < vertices.size(); ++i)
	{
		switch (vertices[i].type)
		{
		case PrimitivePointList:
			if (prTypes != 0)
				*prTypes |= aiPrimitiveType_POINT;
			break;
		case PrimitiveLineList:
			if (prTypes != 0)
				*prTypes |= aiPrimitiveType_LINE;

			i += 1;
			break;
		case PrimitiveTriangleList:
			if (prTypes != 0)
				*prTypes |= aiPrimitiveType_TRIANGLE;

			i += 2;
			break;
		}

		++faces;
	}

	return faces;
}

bool HasNormals(std::vector<D3DVertex>& vertices)
{
	for (auto i: vertices)
		if (i.type == PrimitiveTriangleList && i.norm != aiVector3D())
			return 1;

	return 0;
}

bool HasTexCoords(std::vector<D3DVertex>& vertices)
{
	for (auto i : vertices)
		if (i.texCoord != aiVector2D())
			return 1;

	return 0;
}

bool HasColors(std::vector<D3DVertex>& vertices)
{
	for (auto i : vertices)
		if (i.color != aiColor4D(1.0f))
			return 1;

	return 0;
}

void D3DRegisterImporter(Assimp::Importer& imp)
{
	imp.RegisterLoader(new GMD3DLoader());
}
