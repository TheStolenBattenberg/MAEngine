#pragma once

#include "Types.h"

struct Vertex
{
	float x, y, z;
};

struct Normal
{
	float x, y, z;
};

struct TexCoord
{
	float s, t;
};

struct VertNorm {
	Vertex v;
	Normal n;
};

struct VertTexCoord {
	Vertex   v;
	TexCoord t;
};

struct VertNormalTexCoord {
	Vertex   v;
	Normal   n;
	TexCoord t;
};
