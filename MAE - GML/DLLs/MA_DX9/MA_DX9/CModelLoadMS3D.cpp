#include "CModelLoadMS3D.h"

namespace MS3DType {
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

void CModelLoadMS3D::Load(Mesh* msh, string file) {
	std::ifstream f(file, std::ios::in | std::ios::binary);
	if (!f) {
		return;
	}

	MS3DType::Header h;
	f.read((char*)&h, sizeof(h));

}