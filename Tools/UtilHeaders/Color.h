#pragma once

#include <limits>

template<typename T> struct col4t
{
	col4t(): col4t(getLimit()) { }
	col4t(T r): col4t(r, r, r) { };
	col4t(T r, T g, T b): col4t(getLimit(), r, g, b) { }
	col4t(T _a, T _r, T _g, T _b): a(_a), r(_r), g(_g), b(_b) { }

	template<typename T2> col4t(const col4t<T2>& col)
	{
		a = T(col.a * getLimit() / col.getLimit());
		r = T(col.r * getLimit() / col.getLimit());
		g = T(col.g * getLimit() / col.getLimit());
		b = T(col.b * getLimit() / col.getLimit());
	}

	union
	{
		T data[4];

		struct
		{
			T a, r, g, b;
		};
	};

	static T getLimit()
	{
		return std::is_integral<T>::value ? std::numeric_limits<T>::max() : T(1);
	}

	bool operator==(const col4t<T>& col)
	{
		return memcmp(data, col.data, sizeof(data)) == 0;
	}

	bool Equals(const col4t<T>& col, T epsilon = std::numeric_limits<T>::epsilon())
	{
		if (std::is_integral<T>::value)
			return memcmp(data, col.data, sizeof(data)) == 0;

		return std::abs(a - col.a) < epsilon &&
		       std::abs(r - col.r) < epsilon &&
		       std::abs(g - col.g) < epsilon &&
		       std::abs(b - col.b) < epsilon;
	}
};

typedef col4t<float>         col4f;
typedef col4t<unsigned char> col4u;
