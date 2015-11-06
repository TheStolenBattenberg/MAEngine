#pragma once

/**
 * Includes
 */
#include "Types.h"


/**
 * IDTech 2 Model
 * Version 8
 */
#define MD2_MAGICNUMBER 0x32504449
#define MD2_VERSION 0x08

namespace MD2Type
{
	struct Header
	{
		uint magicNumber;
		uint version;

		uint skinWidth;
		uint skinHeight;
		uint frameSize;

		uint numSkin;
		uint numVert;
		uint numST;
		uint numTris;
		uint numGLCmds;
		uint numFrames;

		uint ofsSkins;
		uint ofsST;
		uint ofsTris;
		uint ofsFrames;
		uint ofsGLCmds;
		uint ofsEnd;
	};

	struct Vertex
	{
		ubyte vertex[3];
		ubyte normInd;
	};

	struct Frame
	{
		float  scale[3];
		float  translate[3];
		char   name[16];
		Vertex verticies[1];
	};

	struct Triangle
	{
		short vertInd[3];
		short texInd[3];
	};

	typedef short IndexBuffer[3];

	struct Texcoord
	{
		short s, t;
	};
};