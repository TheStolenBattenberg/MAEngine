#pragma once

typedef unsigned int   uint;
typedef signed int     sint;
typedef unsigned short ushort;
typedef unsigned char  ubyte;

typedef float mat3[9];
typedef float mat4[16];

struct vec2 {
	union {
		float raw[2];

		struct
		{
			float x, y;
		};
	};
};

struct vec3 {
	union {
		float raw[3];

		struct
		{
			float x, y, z;
		};
	};
};

struct vec4 {
	union {
		float raw[4];

		struct
		{
			float x, y, z, w;
		};
	};
};

struct colourARGB {
	union {
		uint colour;

		struct
		{
			ubyte a, r, g, b;
		};
	};
};

struct colourRGBAF {
	float r, g, b, a;
};
