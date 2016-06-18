#include <MAE/Main.h>
#include <MAE/GMLAPI/GMLMain.h>
#include <MAE/Rendering/Mesh/CModelLoadMSM.h>

namespace MSMType {
	const uint MagicNumber = 0x4D534D66; //MSMf
	const uint Version     = 0x00000001;

	typedef uint IndexBuffer[3];

	struct Header {
		uint MagicNumber;
		uint Version;
		uint VertexCount;
		uint TriangleCount;
		uint MeshCount;
		uint MaterialCount;
	};

	struct Vertex {
		float VP[3];
		float NP[3];
		float U;
		float V;
	};

	struct Triangle {
		uint MeshID;
		uint MaterialID;
		uint VInd[3];
	};

	struct Material {
		float Diffuse[4];
		float Ambient[4];
		float Specular[4];
		float Emissive[4];
		float Power;

		char TexDiffuseName[256];
	};
}

uint CModelLoadMSM::Load(Mesh* mesh, string file) {
	uint i;
	uint MeshID;
	//uint LastMeshID;
	//uint MaterialID;
	//HRESULT res;

	//Open File.
	std::ifstream f(file, std::ios::in | std::ios::binary);
	if (!f) {
		return 0;
	}

	//Read & Verify.
	MSMType::Header h;
	f.read((char*)&h, sizeof(h));
	if (h.MagicNumber != MSMType::MagicNumber && h.Version != MSMType::Version) {
		return 0;
	}

	//Read Vertices into a buffer.
	MSMType::Vertex* VertexBuffer = new MSMType::Vertex[h.VertexCount];
	f.read((char*)VertexBuffer, h.VertexCount * sizeof(MSMType::Vertex));

	//Read Triangles into a buffer.
	MSMType::Triangle* TriangleBuffer = new MSMType::Triangle[h.TriangleCount];
	f.read((char*)TriangleBuffer, h.TriangleCount * sizeof(MSMType::Triangle));

	//Read Materials into a buffer.
	MSMType::Material* MaterialBuffer = new MSMType::Material[h.MaterialCount];
	f.read((char*)MaterialBuffer, h.MaterialCount * sizeof(MSMType::Material));


	Mesh* MeshBuffer = new Mesh[h.MeshCount];

	//Move Index Buffer.
	MSMType::IndexBuffer* IndBuf;
	for (i = 0; i < h.TriangleCount; ++i) {
		MeshID = TriangleBuffer[i].MeshID;
		MeshBuffer[MeshID].m_uiMaterialIndex = TriangleBuffer[i].MaterialID;
		IndBuf[i][0] = TriangleBuffer[i].VInd[0];
		IndBuf[i][1] = TriangleBuffer[i].VInd[1];
		IndBuf[i][2] = TriangleBuffer[i].VInd[2];
	}

	return h.MeshCount;
}