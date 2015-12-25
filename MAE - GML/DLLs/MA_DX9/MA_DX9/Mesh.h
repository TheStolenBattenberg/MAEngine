#pragma once

#include "Types.h"

#include <Vec.h>

typedef vec3 Vertex;
typedef vec3 Normal;

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
