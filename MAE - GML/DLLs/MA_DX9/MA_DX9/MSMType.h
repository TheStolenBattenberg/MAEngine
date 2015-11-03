/**
 * MAE Static Model.
 * Version 1.
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

#define MSM_VERSION 0x00000001

namespace MSMType {
	struct Header {
		char Tag[4]; //Should be 'MSMf'
		int Version; //Depends on version, for this one it's '1'.
		word VertexCount;
		word TriangleCount;
		word MaterialCount;
		byte HasShader;
	};
	struct Triangle {
		word VertexIndex[3];
		float Normal[3][3];
		float S[3];
		float T[3];
	};

	struct MaterialDiffuse {
		float Diffuse[4];
		float Ambient[4];
		float Specular[4];
		float Emissive[4];
		float SpecularPower;
		char Texture[128];
	};

	struct Shader {
		word VShaderNameLength;
		char VShader; //Multiply by VShaderNameLength when loading.
		word PShaderNameLength;
		char PShader; //Multiply by PShaderNameLength when loading.
	};
}