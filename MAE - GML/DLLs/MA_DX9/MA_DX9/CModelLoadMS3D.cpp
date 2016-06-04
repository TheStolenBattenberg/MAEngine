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

	//ushort GroupCount;

	struct Group {
		ubyte  Flags;
		char   Name[32];
		ushort TriangleCount;
		ushort TriangleIndices; //Multiply by TriangleCount.
		ubyte  MaterialIndex;
	};

	//ushort MaterialCount;

	struct Material {
		char  Name[32];
		float Ambient[4];
		float Diffuse[4];
		float Specular[4];
		float Emissive[4];
		float Shininess;
		float Transparency;
		ubyte Mode;
		char  Texture[128];
		char  Alphamap[128];
	};

	//float FPS;
	//float CurrentTime;
	//int   TotalFrames;
	
	//ushort JointCount;

	struct KeyframeRotation {
		float Time;
		float Rotation[3];
	};

	struct KeyframePosition {	
		float Time;
		float Position[3];
	};

	struct Joint {
		ubyte Flags;
		char  Name[32];
		char  ParentName[32];
		float Rotation[3];
		float Position[3];

		ushort KeyframeRotationCount;
		ushort KeyframePositionCount;

		KeyframeRotation KfRot; //Multiply by KeyframeRotationCount;
		KeyframePosition KfPos; //Multiply by KeyframePositionCount;
	};

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