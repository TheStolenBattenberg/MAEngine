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
	vec3(): vec3(0) { }

	vec3(float val): vec3(val, val, val) { }

	vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

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

struct col4u
{
	col4u(): col4u(0xFF) { }

	col4u(ubyte val): col4u(val, val, val) { }

	col4u(ubyte r, ubyte g, ubyte b): col4u(0xFF, r, g, b) { }

	col4u(ubyte a, ubyte r, ubyte g, ubyte b)
	{
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	union
	{
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

struct quat {
	quat(): quat(0, 0, 0, 0) { }

	quat(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	union {
		float raw[4];

		struct
		{
			float x, y, z, w;
		};
	};
};
