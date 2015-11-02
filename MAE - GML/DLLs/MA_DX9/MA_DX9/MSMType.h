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


namespace MSMType {
	struct Header {
		char Tag[4]; //Should be 'MSMf'
		int Version; //Depends on version, for this one it's '1'.
		word VertexCount;
		word NormalCount;
		word TexcoordCount;
		word TriangleCount;
		word MaterialCount;
		byte MaterialType; //1 == Diffuse, 2 == Texture
		byte HasShader;
	};

	struct Vertices {
		float Vertex[3];
	};

	struct Normal {
		float Norm[3];
	};

	struct Texcoord {
		float S[3];
		float T[3];
	};

	struct Triangle {
		byte Group;
		word VertexIndex[3];
		word NormalIndex[3];
		word TexcoordIndex[3];
	};

	struct MaterialDiffuse {
		byte Group;
		byte Diffuse[4];
	};

	struct MaterialTexture {
		byte Group;
		char Texture[128]; //Should probably make this part able to be over ridden.
	};

	struct Shader {
		word VShaderNameLength;
		char VShader; //Multiply by VShaderNameLength when loading.
		word PShaderNameLength;
		char PShader; //Multiply by PShaderNameLength when loading.
	};
}