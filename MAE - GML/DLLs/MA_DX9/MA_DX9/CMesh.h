#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Types.h"
#include "Texture.h"

struct Mesh {
	uint                    m_uiMaterialIndex;

	uint                    m_uiVertexCount;
	uint                    m_uiNormalCount;
	uint                    m_uiPolyCount;

	LPDIRECT3DVERTEXDECLARATION9 m_VD;
	LPDIRECT3DVERTEXBUFFER9      m_VB;
	LPDIRECT3DINDEXBUFFER9       m_IB;
};

struct Material {
	D3DMATERIAL9 m_mMaterial;
	Texture*     m_pTexture;
};

struct Vertex {
	float x, y, z;
};

struct Normal {
	float x, y, z;
};

struct TexCoord {
	float u, v;
};

struct NormTexCoord {
	Normal   n;
	TexCoord t;
};

struct VertNormTexCoord {
	Vertex   v;
	Normal   n;
	TexCoord t;
};