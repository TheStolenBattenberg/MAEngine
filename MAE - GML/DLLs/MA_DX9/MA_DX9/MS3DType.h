/**
*
* NOTE :-> This MS3DType is based upon this spesification by Mete Ciragan: http://paulbourke.net/dataformats/ms3d/ms3dspec.h
*
*/

/**
 * Types.
 */
#ifndef byte
	typedef unsigned char byte;
#endif

#ifndef word
	typedef unsigned short word;
#endif

namespace MS3DType {
	struct Header {
		char Tag[10];
		int Version;
	};

	word VertexCount;

	struct Vertices {
		byte Flags;
		float Vertex[3];
		char BoneId;
		byte ReferenceCount;
	};

	word TriangleCount;

	struct Triangle {
		word Flags;
		word VertexIndices[3];
		float VertexNormals[3][3];
		float S[3];
		float T[3];
		byte SmoothingGroup;
		byte GroupIndex;
	};

	word GroupCount;

	struct Group {
		byte Flags;
		char Name[32];
		word TriangleNumber;
		word TriangleIndices; //Multiply this by TriangleNumber during loading.
		char MaterialIndex;
	};

	word MaterialCount;

	struct Material {
		char Name[32];
		float Ambient[4];
		float Diffuse[4];
		float Specular[4];
		float Emissive[4];
		float Shininess;
		float Transparency;
		char Mode;
		char Texture[128]; //Should probably make this part able to be over ridden.
		char Alphamap[128];
	};

	float FPS;
	float CurrentTime;
	int TotalFrames;

	word JointCount;

	struct KeyframeRotation {
		float Time;
		float Rotation;
	};

	struct KeyframePosition {
		float Time;
		float Position;
	};

	struct Joint {
		byte Flags;
		char Name[32];
		char ParentName[32];
		float Rotation[3];
		float Position[3];

		word KeyframeRotationNumber;
		word KeyframePositionNumber;

		KeyframeRotation keyFramesRot; //Multiply this by KeyframeRotationNumber during loading.
		KeyframePosition keyFramesPos; //Multiply this by KeyframePositionNumber during loading.
	};
}