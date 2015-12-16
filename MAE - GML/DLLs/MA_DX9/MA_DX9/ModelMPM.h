#pragma once 

/**
 * Includes
 */

#include "Types.h" 

/**
 * MAE Packet Model
 * Version 1
 */

namespace MPMModel
{
	const uint MagicNumber = 0x464D504D;
	const uint Version = 0x00000001;

	enum Packets
	{
		PacketMeshesID             = 0x4853454D,
		PacketMaterialID           = 0x0054414D,
		PacketVertexDescID         = 0x43534544,
		PacketVertexDataID         = 0x54524556,
		PacketVertexDataPerIndexID = 0x44444E49,
		PacketVertexIndexID        = 0x00444E49,
		PacketBonesID              = 0x454E4F42,
		PacketMorphTargetID        = 0x00534F50,
		PacketCollisionsID         = 0x004C4F43,
		PacketAnimationID          = 0x4D494E41
	};

	/**
	 * Header
	 */

	struct Header
	{
		uint   magicNumber;
		ushort version;
		ushort compVersion; // Min version supported
		uint   numPackets;
		uint   numMeshes;
		uint   numMaterials;
	};

	struct PacketHeader
	{
		uint id;
		uint length;
	};

	struct Mesh
	{
		uint meshInd;
		uint matInd;
		vec3 trans;
		vec3 scal;
		quat rot;
	};

	struct Material
	{
		col4u ambient;
		col4u diffuse;
		col4u specular;
		float reflectivity;     // 0 or less when not reflecting
		char  tex[128];         // empty if no texture is used
		char  shader[128];      // empty if no shader is used
		char  environment[128]; // empty if no enivornment map is used
	};

	struct PacketVertexDescHeader
	{
		uint meshInd;
		uint num; // Number of PacketVertexDesc structs
		uint vertStride;
		uint instStride;
		uint morphTargetStride;
	};

	struct PacketVertexDesc
	{
		enum Flags
		{
			FlagPerIndex = 0x01, // Data is stored per index
			FlagPerFrame = 0x02  // Data is stored per frame. Only valid when used with UsagePosition and UsageNormal
		};

		enum Usage
		{
			UsagePosition   = 0x01,
			UsageTexCoords  = 0x02,
			UsageNormals    = 0x03,
			UsageColor      = 0x04,
			UsageBoneIndex  = 0x05, // Can be defined more than once
			UsageBoneWeight = 0x06  // Same thing applies to this
		};

		enum Types
		{
			TypeFloat = 0x01,
			TypeVec2  = 0x02,
			TypeVec3  = 0x03,
			TypeVec4  = 0x04,
			TypeColor = 0x05,
			TypeInt   = 0x06
		};

		ushort flags;
		ubyte  usage;
		ubyte  type;
		ushort offset;
	};

	struct PacketVertexIndex
	{
		enum Types
		{
			TypeU16 = 0x01,
			TypeU32 = 0x02
		};

		uint meshInd;
		uint num;
		uint type;
	};

	struct PacketBonesHeader
	{
		uint meshInd;
		uint num;
		uint frames;
	};

	struct PacketBonesFrameHeader
	{
		uint time; // In ms. Indicates when the frame begins
	};

	struct PacketBones
	{
		vec3 trans;
		vec3 scal;
		quat rot;
	};

	struct PacketMorphTargetHeader
	{
		uint meshInd;
		uint size;
		uint frames;
	};

	struct PacketMorphTargetFrameHeader
	{
		uint time; // In ms. Indicates when the frame begins
	};

	struct PacketAnimationHeader
	{
		uint meshInd;
		uint num;
	};

	struct PacketAnimation
	{
		char name[64];
		uint start;
		uint end;
	};
}
