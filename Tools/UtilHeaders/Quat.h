#pragma once

#include <math.h>

template<typename T> union quatt
{
	quatt(): x(T(0)), y(T(0)), z(T(0)), w(T(1)) { }
	quatt(T _x, T _y, T _z, T _w): x(_x), y(_y), z(_z), w(_w) { }

	T data[4];

	struct
	{
		T x, y, z, w;
	};

	static quatt<T> slerp(const quatt<T>& beg, const quatt<T>& end, T factor)
	{
		/**
		* Adopted version of Assimps Interpolate function which is based on the gmtl library
		*/

		T cosom = beg.x * end.x + beg.y * end.y + beg.z * end.z + beg.w * end.w;

		quatt tend = end;

		if (cosom < T(0))
		{
			cosom = -cosom;

			tend.x = -tend.x;
			tend.y = -tend.y;
			tend.z = -tend.z;
			tend.w = -tend.w;
		}

		T sclp, sclq;

		if (T(1) - cosom > T(0.0001))
		{
			T omega = std::acos(cosom);
			T sinom = std::sin(omega);
			sclp = std::sin((T(1) - factor) * omega) / sinom;
			sclq = std::sin(factor * omega) / sinom;
		}
		else
		{
			sclp = T(1) - factor;
			sclq = factor;
		}

		return quatt<T>(sclp * beg.x + sclq * tend.x,
		                sclp * beg.y + sclq * tend.y,
		                sclp * beg.z + sclq * tend.z,
		                sclp * beg.w + sclq * tend.w);
	}
};

typedef quatt<float> quat;
