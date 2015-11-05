#pragma once

#include <d3d9.h>
#include <string>

class Shader {
public:
	~Shader();

	bool compile(std::string vert, std::string pixel);

	LPDIRECT3DVERTEXSHADER9 VShader    = 0;
	LPDIRECT3DPIXELSHADER9  PShader    = 0;
	LPD3DXCONSTANTTABLE     VConstants = 0;
	LPD3DXCONSTANTTABLE     PConstants = 0;
};

class Texture {
public:
	enum MipMaps {
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	~Texture();

	bool loadFromFile(std::string file, MipMaps mipmaps);

	LPDIRECT3DTEXTURE9 tex = 0;
};
