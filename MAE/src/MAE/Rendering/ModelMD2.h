#pragma once

/**
 * Includes
 */

#include <MAE/Core/Types.h>
#include <MAE/Rendering/Resources/Texture.h>

#include <vector>

class MD2Model
{
public:
	~MD2Model();

	void load(std::string model, bool normals);
	void setTexture(Texture* tex);
	void render(Renderer* renderer, uint frame1, uint frame2, float tween);
	uint getFrameCount();

private:
	uint vertCount = 0;
	uint triCount = 0;

	Texture* tex = 0;

	LPDIRECT3DVERTEXDECLARATION9 decl = 0;

	std::vector<LPDIRECT3DVERTEXBUFFER9> vertBufs;
	LPDIRECT3DVERTEXBUFFER9 texBuf = 0;
	LPDIRECT3DINDEXBUFFER9 indBuf = 0;

	bool normals = 0;
};
