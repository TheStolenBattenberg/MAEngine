#pragma once

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  ubyte;

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef float mat3[9];
typedef float mat4[16];

struct Vector2D {
	float x;
	float y;
};

struct Vector3D {
	float x;
	float y;
	float z;
};

struct ColourRGBA {
	float r;
	float g;
	float b;
	float a;
};