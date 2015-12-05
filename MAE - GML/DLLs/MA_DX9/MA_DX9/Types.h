#pragma once

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  ubyte;

typedef float mat3[9];
typedef float mat4[16];

struct vec2 {
	union {
		float raw[2];
		float x, y;
	};
};

struct vec3 {
	union {
		float raw[3];
		float x, y, z;
	};
};

struct vec4 {
	union {
		float raw[4];
		float x, y, z, w;
	};
};

struct colourARGB {
	union {
		uint colour;
		ubyte a, r, g, b;
	};
};

struct colourRGBAF {
	float r, g, b, a;
};
