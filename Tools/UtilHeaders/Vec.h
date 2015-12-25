#pragma once

#include <math.h>
#include <type_traits>

struct _vecct_dummy { };

template<std::size_t C, typename T> struct _vecct;

template<std::size_t C, typename T> struct vecct: _vecct<C, T>
{
	static const std::size_t components = C;

	vecct(): vecct(T(0)) { }

	vecct(T x)
	{
		for (auto& i : data)
			i = x;
	}

	template<typename... Args> vecct(typename std::conditional<sizeof...(Args) + 1 == C, T, _vecct_dummy>::type head, Args... args)
	{
		T arr[] = {head, T(args)...};

		for (std::size_t i = 0; i < C; ++i)
			data[i] = arr[i];
	}

	template<std::size_t C2> vecct(const vecct<C2, T>& vec)
	{
		if (C2 > C)
			for (std::size_t i = 0; i < C; ++i)
				data[i] = vec[i];
		else
		{
			for (std::size_t i = 0; i < C2; ++i)
				data[i] = vec[i];

			for (std::size_t i = C2; i < C; ++i)
				data[i] = T(0);
		}
	}

	T lengthSqr() const
	{
		T sum = 0;

		for (auto i : data)
			sum += i * i;

		return sum;
	}

	T length() const
	{
		return std::sqrt(lengthSqr());
	}

	vecct<C, T>& normalize()
	{
		T l = length();

		if (l != T(0))
			*this /= l;

		return *this;
	}

	vecct<C, T> normalized() const
	{
		vecct<C, T> vec = *this;

		T l = vec.length();

		if (l != T(0))
			vec /= l;

		return vec;
	}

	T& operator[](std::size_t index)
	{
		return data[index];
	}

	const T& operator[](std::size_t index) const
	{
		return data[index];
	}

	T operator*(const vecct<C, T>& vec) const
	{
		T sum = T(0);

		for (std::size_t i = 0; i < C; ++i)
			sum += data[i] * vec.data[i];

		return sum;
	}

	vecct<C, T> operator*(T value) const
	{
		vecct<C, T> ret;

		for (std::size_t i = 0; i < C; ++i)
			ret.data[i] = data[i] * value;

		return ret;
	}

	vecct<C, T> operator/(T value) const
	{
		vecct<C, T> ret;

		for (std::size_t i = 0; i < C; ++i)
			ret.data[i] = data[i] / value;

		return ret;
	}

	vecct<C, T>& operator*=(T value)
	{
		for (auto& i : data)
			i *= value;

		return *this;
	}

	vecct<C, T>& operator/=(T value)
	{
		for (auto& i : data)
			i /= value;

		return *this;
	}
};

template<std::size_t C, typename T> struct _vecct
{
	T data[C];
};

template<typename T> struct _vecct<2, T>
{
	union
	{
		T data[2];

		struct
		{
			T x, y;
		};
	};
};

template<typename T> struct _vecct<3, T>
{
	union
	{
		T data[3];

		struct
		{
			T x, y, z;
		};
	};
};

template<typename T> struct _vecct<4, T>
{
	union
	{
		T data[4];

		struct
		{
			T x, y, z, w;
		};
	};
};

typedef vecct<2, float> vec2;
typedef vecct<3, float> vec3;
typedef vecct<4, float> vec4;
