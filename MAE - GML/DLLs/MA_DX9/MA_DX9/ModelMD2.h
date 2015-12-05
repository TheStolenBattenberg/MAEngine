#pragma once

/**
 * Includes
 */

#include "Types.h"

class MD2Model: public Object
{
public:
	~MD2Model();

	bool load(std::string model, bool normals);
	void setTexture(LPDIRECT3DTEXTURE9 tex);
	void render(uint frame1, uint frame2, float tween);
	uint getFrameCount();

private:
	uint vertCount = 0;
	uint triCount = 0;

	LPDIRECT3DTEXTURE9 tex = 0;

	LPDIRECT3DVERTEXDECLARATION9 decl = 0;

	std::vector<LPDIRECT3DVERTEXBUFFER9> vertBufs;
	LPDIRECT3DVERTEXBUFFER9 texBuf = 0;
	LPDIRECT3DINDEXBUFFER9 indBuf = 0;

	bool normals = 0;
};
