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
	~Texture();

	bool loadFromFile(std::string file, bool mipmaps);
	void upload();
	void freeGPU();

	LPDIRECT3DTEXTURE9 texSys = 0;
	LPDIRECT3DTEXTURE9 texGPU = 0;
};
