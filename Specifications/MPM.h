#pragma once

#include <stdint.h>
#include <Vec.h>
#include <Mat.h>
#include <Color.h>
#include <Quat.h>

/**
 * MAE Packet Model
 * Version 1
 */

namespace MPM
{
	const uint32_t MagicNumber = 0x464D504D;
	const uint32_t Version     = 0x00000001;
	const uint32_t CompVersion = 0x00000001;

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
		uint32_t magicNumber;
		uint16_t version;
		uint16_t compVersion; // Min version supported
		uint32_t numMeshes;
		uint32_t numMaterials;
	};

	struct PacketHeader
	{
		uint32_t id;
		uint32_t length;
	};

	struct InstHeader
	{
		uint32_t num;
	};

	struct Inst
	{
		uint32_t meshInd;
		vec3     trans;
		vec3     scal;
		quat     rot;
	};

	struct MaterialHeader
	{
		uint32_t num;
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
		uint32_t meshId;
		uint32_t matInd;
		uint32_t numVertices;
		uint32_t numIndices;
	};

	struct PacketVertexDescHeader
	{
		uint32_t meshInd;
		uint32_t num;               // Number of PacketVertexDesc structs
		uint32_t vertStride;
		uint32_t morphTargetStride;
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

		uint16_t flags;
		uint8_t  usage;
		uint8_t  type;
		uint16_t offset;
	};

	struct PacketVertexDataHeader
	{
		uint32_t meshInd;
		uint32_t length;
	};

	struct PacketVertexIndexHeader
	{
		enum Types
		{
			TypeU16 = 0x01,
			TypeU32 = 0x02
		};

		uint32_t meshInd;
		uint32_t num;
		uint32_t type;
	};

	struct PacketBonesHeader
	{
		uint32_t meshInd;
		uint32_t num;
		uint32_t frames;
	};

	struct PacketBonesFrameHeader
	{
		uint32_t time; // In ms. Indicates when the frame begins
	};

	struct PacketBones
	{
		vec3 trans;
		vec3 scal;
		quat rot;
	};

	struct PacketMorphTargetHeader
	{
		uint32_t meshInd;
		uint32_t size;
		uint32_t frames;
	};

	struct PacketMorphTargetFrameHeader
	{
		uint32_t time; // In ms. Indicates when the frame begins
	};

	struct PacketAnimationHeader
	{
		uint32_t meshInd;
		uint32_t num;
	};

	struct PacketAnimation
	{
		char name[64];
		uint32_t start;
		uint32_t end;
	};
}
