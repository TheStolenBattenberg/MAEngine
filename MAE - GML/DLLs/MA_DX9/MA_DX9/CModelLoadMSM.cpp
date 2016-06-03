#include "CModelLoadMSM.h"

namespace MSMType {
	const uint MagicNumber = 0x4D534D66; //MSMf
	const uint Version     = 0x00000001;

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

void CModelLoadMSM::Load(std::vector<Mesh> *mesh, string file) {
	uint i;
	uint MeshID;
	uint MaterialID;

	/*
	D3DVERTEXELEMENT9 elem[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	*/

	//Open File.
	std::ifstream f(file, std::ios::in | std::ios::binary);
	if (!f) {
		return;
	}

	//Read & Verify Header.
	MSMType::Header h;
	f.read((char*)&h, sizeof(h));
	if (h.MagicNumber != MSMType::MagicNumber && h.Version != MSMType::Version) {
		return;
	}

	//Read Vertices into a buffer.
	VertNormTexCoord* VertexBuffer;
	for (i = 0; i < h.VertexCount; ++i) {
		f.read((char*)&VertexBuffer[i], sizeof(MSMType::Vertex));
	}
}