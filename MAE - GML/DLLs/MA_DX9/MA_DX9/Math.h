#pragma once

#include "Types.h"
#include <Windows.h>
#include <math.h>

//Random
float randomRangef(float min, float max);
uint  randomRange(uint min, uint max);
	
//Interpolation
float interpLinear(float x, float y, float s);
float interpCosine(float x, float y, float s);
float interpCubic(float x, float y, float z, float w, float s);