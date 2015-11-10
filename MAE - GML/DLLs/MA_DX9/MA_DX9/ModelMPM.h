#pragma once 


/**
 * Includes
 */
#include "Types.h" 

/**
 * MAE Packet Model
 * Version 1
 */
#define MPM_MAGICNUMBER 0x664D504D //MPMf
#define MPM_VERSION 0x01 //1

namespace MPMModel 
{
	enum Packets {
		Packet_PkSD = 0x44536B50, //Static Data Packet Identifier.
		Packet_PkGD = 0x44476B50, //Geometry Data Packet Identifier.
		Packet_PkAD = 0x44416B50, //Animated Data Packet Identifier.
		Packet_PkCD = 0x44436B50, //Collision Data Packet Identifier.     
		Packet_PkMD = 0x444D6B50, //Material Data Packet Identifier.
		Packet_PkTD = 0x44546B50, //Texture Data Packet Identifier.
		Packet_PkV0 = 0x30566B50, //Vertex Packet Identifier.
		Packet_PkN0 = 0x304E6B50, //Normal Packet Identifier.
		Packet_PkT0 = 0x30546B50, //Texcoord Packet Identifier.
		Packet_PkF0 = 0x30466B50, //Face Packet Identifier.
	};

	/**
	 * Header.
	 */
	struct Header {
		uint magicNumber;
		uint version;
		uint numPacket;
	};

	typedef uint PacketId; //The packetID.
	typedef uint nextPacketOffset; //If the packetID was unrecognised, skip to the next packet using this.


	/**
	 * Used to contain static model data, with no animation.
	 * The reason for this data type is because GeometryData doesn't support multitexturing, this does.
	 */
	struct PacketStaticData { //PkSD
		uint numLoD;
		uint numGroup;
		uint numVertex;
		uint numNormal;
		uint numTexcoord;
		uint numFace;
	};


	/**
	 * Used to contain simple direct to vertex buffer data.
	 * If this is used, you will only find the possible other packet typess:
	 * - Shader (This might not be here, it's only used for terrain splatting shaders).
	 * - Material (The index is always 0, there is only one material on geometry).
	 *
	 * This should probably be done a different way, but it will do for now.
	 */
	struct PacketGeometryData { //PkGD
		uint numFace;
		float Vertex[3];
		float Normal[3];
		float Texcoord[2];
	};


	/**
	 * Used to contain information on the animated data.
	 * To-do. Should probably contain information on if the file is a skeletal animation or
	 * morph target animation.
	 */
	struct PacketAnimationData { //PkAD
		//Not implemented, I have no idea how to handle animation data.
	};


	/**
	 * Used to contain a simplified trimesh for sending to bullet.
	 */
	struct PacketCollisionData { //PkCD
		uint numVertex;
		float Vertex[3];
	};


	/**
	 * Used to contain information on materials.
	 * If this packet isn't in a model, it should generate materials * the number of groups.
	 */
	struct PacketMaterialData {
		uint numMaterial;
	};

	/**
	 * Used to hold pure RGBA byte values for a texture.
	 * I haven't implemented it because I'm unsure if it would actually be useful or not.
	 */
	struct PacketTextureData {
		
	};


	/**
	 * Used to contain Vertices.
	 */
	struct PacketVertex { //PkV0, 
		float Vertex[3];
	};


	/**
	 * Used to contain Normals.
	 */
	struct PacketNormal { //PkN0
		float Normal[3];
	};


	/**
	 * Used to contain Texcoords.
	 */
	struct PacketTexcoord { //PkT0
		float Texcoord[2];
	};


	/**
	 * Used to contain Indicies & the material Index.
	 */
	struct PacketFace { //PkF0
		uint VertexIndices[3];
		uint NormalIndices[3];
		uint TexcoordIndices[2];
		uint MaterialIndex;
	};


	/**
	 * Used to contain a material for D3D.
	 * It's the same format as a D3DMATERIAL9 struct, so we should be able to make materials directly from this data.
	 */
	struct PacketMaterial {
		float Diffuse[4];
		float Ambient[4];
		float Specular[4];
		float Emmissive[4];
		float SpecularPower;
	};
}