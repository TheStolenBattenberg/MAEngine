#pragma once

/**
 * Includes
 */
#include "Types.h"


/**
 * MAE Static Model
 * Version 1
 */
#define MSM_MAGICNUMBER 0x664D534D
#define MSM_VERSION 0x01

namespace MSMType {    
    struct Vertex {
        float vX; //Position
        float vY;
        float vZ;
		float nX; //Normal
		float nY;
		float nZ;
		float tU; //Texcoord
		float tV;
	};
    
	struct Triangle {
		ushort VertexIndex[3];
	};

	struct Material {
		float Diffuse[4];
		float Ambient[4];
		float Specular[4];
		float Emissive[4];
		float SpecularPower;
	};

	struct Shader {
		ushort VShaderNameLength;
		char VShader; //Multiply by VShaderNameLength when loading.
		ushort PShaderNameLength;
		char PShader; //Multiply by PShaderNameLength when loading.
	};
    
	struct Header {
		uint magicNumber;
		uint Version;
		ushort MeshCount;
	};

    struct Mesh {
		ushort VertexCount;
		ushort TriangleCount;
        byte HasShader;
        
        Vertex MeshVertex;
        Triangle MeshTriangle;
        Material MeshMaterial;
        Shader MeshShader;
    };
}