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
	float interp = (float)(1 - cos(s*3.14)) / 2;
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