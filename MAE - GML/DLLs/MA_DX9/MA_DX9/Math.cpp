#include "Math.h"

/**
 * Interpolation methods are based on code from this article by Paul Bourke.
 * > http://paulbourke.net/miscellaneous/interpolation/
 */

float randomRangef(float min, float max) { //These need random seeds generating somehow. < srand((uint)time(NULL)); is bad >
	return (float)rand() / RAND_MAX * (max - min) + min;
}

uint randomRange(uint min, uint max) {
	return (uint)rand() / RAND_MAX * (max - min) + min;
}

float interpLinear(float x, float y, float s) {
	return (x * (1 - s) + y*s);
}

float interpCosine(float x, float y, float s) {
	float interp = (float)(1 - cos(s*M_PI)) / 2;
	return (x * (1 - interp) + y*interp);
}

float interpCubic(float x, float y, float z, float w, float s) {
	float s1 = s*s;
	float x1 = w - z - x + y;
	float y1 = x - y - x1;
	float z1 = z - x;
	float w1 = y;

	return (x1*s*s1 + y1*s1 + z1*s + w1);
}

float distance1D(float x1, float x2) {
	return x2 - x1;
}

//Would using pow(coord1, coord2) be faster? Probably not. Avoiding sqrt(value) would.
float distance2D(float x1, float y1, float x2, float y2) { 
	float xd, yd; 
	xd = x2 - x1; 
	yd = y2 - y1;

	return (float)sqrt((xd*xd) + (yd*yd));
}

float distance3D(float x1, float y1, float z1, float x2, float y2, float z2) {
	float xd, yd, zd;
	xd = x2 - x1;
	yd = y2 - y1;
	zd = z2 - z1;

	return (float)sqrt((xd*xd) + (yd*yd) + (zd*zd));
}