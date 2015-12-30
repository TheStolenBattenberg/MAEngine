#pragma once
#define _USE_MATH_DEFINES

#include "Types.h"
#include <Windows.h>
#include <cmath>

//Random
float randomRangef(float min, float max);
uint  randomRange(uint min, uint max);
	
//Interpolation
float interpLinear(float x, float y, float s);
float interpCosine(float x, float y, float s);
float interpCubic(float x, float y, float z, float w, float s);

//Distance
float distance1D(float x1, float x2); //Pretty pointless.
float distance2D(float x1, float y1, float x2, float y2);
float distance3D(float x1, float y1, float z1, float x2, float y2, float z2);