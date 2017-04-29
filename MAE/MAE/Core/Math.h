#pragma once

#include <MAE/Core/Types.h>
#include <Windows.h>
#include <cmath>
#include <algorithm>

#include <MAE/Core/Vec.h>

const double PI = 3.1415926535897932384626433832795;

template<typename T, typename F> T interpLinear(T x, T y, F s)
{
	return T(x * (F(1) - s) + y * s);
}

template<typename T, typename F> T interpCosine(T x, T y, F s)
{
	return interpLinear(x, y, (F(1) - std::cos(s * F(PI))) / F(2));
}

template<typename T> inline T clamp(T value, T min, T max)
{
	return std::min(std::max(value, min), max);
}

inline uint irandom_range(uint min, uint max) {
	return (uint)(rand() % (max - min));
}

inline float random_range(float min, float max) {
	return (float)(rand() % (uint)(max - min));
}

inline uint irandom(uint max) {
	return (uint)((rand() / RAND_MAX) * max);
}

inline float random(float max) {
	return (float)((rand() / RAND_MAX) * max);
}