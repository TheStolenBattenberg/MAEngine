#pragma once 

/**
 * Includes
 */

#include "Types.h"

#include <Vec.h>
#include <Quat.h>
#include <Color.h>

/**
 * MAE Packet Model
 * Version 1
 */

namespace MPMModel
{
	const uint MagicNumber = 0x464D504D;
	const uint Version     = 0x00000001;
	const uint CompVersion = 0x00000001;

	enum Packets
	{
		PacketInstID            = 0x54534E49,
		PacketMaterialID        = 0x0054414D,
		PacketMeshID            = 0x4853454D,
		PacketVertexDescID      = 0x43534544,
		PacketVertexDataID      = 0x54524556,
		PacketVertexIndexDataID = 0x00444E49,
		PacketBonesID           = 0x454E4F42,
		PacketMorphTargetID     = 0x00534F50,
		PacketCollisionsID      = 0x004C4F43,
		PacketAnimationID       = 0x4D494E41,
		PacketEndOfFileID       = 0x21464F45
	};

	/**
	 * Header
	 */

	struct Header
	{
		uint   magicNumber;
		ushort version;
		ushort compVersion; // Min version supported
		uint   numMeshes;
		uint   numMaterials;
	};

	struct PacketHeader
	{
		uint id;
		uint length;
	};

	struct InstHeader
	{
		uint num;
	};

	struct Inst
	{
		uint meshInd;
		vec3 trans;
		vec3 scal;
		quat rot;
	};

	struct MaterialHeader
	{
		uint num;
	};

	struct Material
	{
		col4u ambient;
		col4u diffuse;
		col4u emissive;
		col4u specular;
		float reflectivity;    // 0 or less when not reflecting
		char  tex[64];         // empty if no texture is used
		char  shader[64];      // empty if no shader is used
		char  environment[64]; // empty if no enivornment map is used
	};

	struct Mesh
	{
		uint meshId;
		uint matInd;
		uint numVertices;
		uint numIndices;
	};

	struct PacketVertexDescHeader
	{
		uint meshInd;
		uint num;               // Number of PacketVertexDesc structs
		uint vertStride;
		uint morphTargetStride;
	};

	struct PacketVertexDesc
	{
		enum Flags
		{
			FlagPerFrame = 0x01  // Data is stored per frame. Only valid when used with UsagePosition and UsageNormal
		};

		enum Usage
		{
			UsagePosition   = 0x01,
			UsageNormal     = 0x02,
			UsageTexCoord   = 0x03,
			UsageColor      = 0x04,
			UsageBoneIndex  = 0x05, // Can be defined more than once
			UsageBoneWeight = 0x06  // Same thing applies to this
		};

		enum Types
		{
			TypeVec1   = 0x01,
			TypeVec2   = 0x02,
			TypeVec3   = 0x03,
			TypeVec4   = 0x04,
			TypeColor  = 0x05,
			TypeUByte4 = 0x06,
			TypeShort2 = 0x07,
			TypeShort4 = 0x08
		};

		ushort flags;
		ubyte  usage;
		ubyte  type;
		ushort offset;
	};

	struct PacketVertexIndexHeader
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
