#pragma once

#include <MAE/Core/Types.h>
#include <Windows.h>
#include <cmath>
#include <algorithm>

#include <Vec.h>

const double PI = 3.1415926535897932384626433832795;

template<typename T, typename F> T interpLinear(T x, T y, F s)
{
	return T(x * (F(1) - s) + y * s);
}

template<typename T, typename F> T interpCosine(T x, T y, F s)
{
	return interpLinear(x, y, (F(1) - std::cos(s * F(PI))) / F(2));
}

template<typename T> T interpCubic(T x, T y, T z, T s)
{
	T s1 = s * s;
	T x1 = w - z - x + y;
	T y1 = x - y - x1;
	T z1 = z - x;
	T w1 = y;

	return (x1 * s * s1 + y1 * s1 + z1 * s + w1);
}

template<typename T> T distance2D(T x1, T y1, T x2, T y2)
{
	return (vecct<2, T>(x1, y1) - vecct<2, T>(x2, y2)).length();
}

template<typename T> T distance3D(T x1, T y1, T z1, T x2, T y2, T z2)
{
	return (vecct<3, T>(x1, y1, z1) - vecct<3, T>(x2, y2, z2)).length();
}

template<typename T> T radToDeg(T rad)
{
	return rad / T(PI) * T(180);
}

template<typename T> T degToRad(T deg)
{
	return deg / T(180) * T(PI);
}

template<typename T> inline T clamp(T value, T min, T max)
{
	return std::min(std::max(value, min), max);
}
