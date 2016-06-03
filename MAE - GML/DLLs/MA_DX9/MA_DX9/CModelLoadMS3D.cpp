#include "CModelLoadMS3D.h"

namespace MS3DType {
	const string MagicNumber = "MS3D000000";
	const uint   Version     =  0x00000004;

	struct Header {
		char MagicNumber[10];
		uint Version;
	};

	//ushort VertexCount;

	struct Vertex {
		ubyte Flags;
		float Vert[3];
		ubyte BoneID;
		ubyte ReferenceCount;
	};

	//ushort TriangleCount;

	struct Triangle {
		ushort Flags;
		ushort VertexIndex[3];
		float  Normal[3][3];
		float  S[3];
		float  T[3];
		ubyte  SmoothingGroup;
		ubyte  GroupIndex;
	};

	// There's a lot more to the MS3D Header, but we'll leave it like this for now, as this is the data I want. What's left is:
	//     Groups
	//     Materials
	//     Keyframes
	//     Comments
	//     Extra Vertex Information (Vertex Weights)
	//
	// Mesh Transformation:
	// 
	// 0. Build the transformation matrices from the rotation and position
	// 1. Multiply the vertices by the inverse of local reference matrix (lmatrix0)
	// 2. then translate the result by (lmatrix0 * keyFramesTrans)
	// 3. then multiply the result by (lmatrix0 * keyFramesRot)
	//
	// For normals skip step 2.
	//
}

void CModelLoadMS3D::Load(std::vector<Mesh> *mesh, string file) {
	ushort i;
	
	//Open File.
	std::ifstream f(file, std::ios::in | std::ios::binary);
	if (!f) {
		return;
	}

	//Read & Verify Header.
	MS3DType::Header h;
	f.read((char*)&h, sizeof(h));
	if (h.MagicNumber != MS3DType::MagicNumber && h.Version != MS3DType::Version) {
		return;
	}
}