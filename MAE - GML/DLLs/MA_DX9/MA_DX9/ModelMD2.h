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

class MD2Model : public Object {
public:
	~MD2Model();

	bool load(std::string model);
	void setTexture(LPDIRECT3DTEXTURE9 tex);

	LPDIRECT3DVERTEXBUFFER9 getVB(uint frame);
	LPDIRECT3DVERTEXBUFFER9 getTB();
	LPDIRECT3DINDEXBUFFER9  getIB();
	LPDIRECT3DTEXTURE9      getTex();

	uint getVertCount();
	uint getTriCount();
	uint getFrameCount();

private:
	uint vertCount = 0;
	uint triCount = 0;

	LPDIRECT3DTEXTURE9 tex = 0;

	std::vector<LPDIRECT3DVERTEXBUFFER9> vertBufs;
	LPDIRECT3DVERTEXBUFFER9 texBuf = 0;
	LPDIRECT3DINDEXBUFFER9 indBuf = 0;
};