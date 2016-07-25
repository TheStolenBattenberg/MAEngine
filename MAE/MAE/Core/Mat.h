#pragma once

#include <Math.h>
#include <type_traits>

template<std::size_t C, typename T> struct vecct;
template<typename T> union quatt;

struct _matst_dummy { };

template<std::size_t S, typename T> struct _matst;

template<std::size_t S, typename T> struct matst: _matst<S, T>
{
	static const std::size_t size = S;

	matst()
	{
		for (auto& i : data)
			i = T(0);

		for (std::size_t i = 0; i < S; ++i)
			data[i * (1 + S)] = T(1);
	}

	template<typename... Args> matst(typename std::conditional<sizeof...(Args) + 1 == S * S, T, _matst_dummy>::type head, Args... args)
	{
		T arr[] = {head, T(args)...};

		for (std::size_t i = 0; i < S * S; ++i)
			data[i] = arr[i];
	}

	template<std::size_t S2> matst(const matst<S2, T>& mat)
	{
		if (S2 > S)
			for (std::size_t j = 0; j < S; ++j)
				for (std::size_t i = 0; i < S; ++i)
					(*this)(i, j) = mat(i, j);
		else
		{
			*this = matst<S, T>();

			for (std::size_t j = 0; j < S2; ++j)
				for (std::size_t i = 0; i < S2; ++i)
					(*this)(i, j) = mat(i, j);
		}
	}

	matst(const quatt<T>& q)
	{
		static_assert(S >= 3, "Must atleast have a size of 3");

		*this = matst<S, T>();

		(*this)(0, 0) = T(1) - T(2) * (q.y * q.y + q.z * q.z);
		(*this)(1, 0) = T(2) * (q.x * q.y - q.z * q.w);
		(*this)(2, 0) = T(2) * (q.x * q.z + q.y * q.w);
		(*this)(0, 1) = T(2) * (q.x * q.y + q.z * q.w);
		(*this)(1, 1) = T(1) - T(2) * (q.x * q.x + q.z * q.z);
		(*this)(2, 1) = T(2) * (q.y * q.z - q.x * q.w);
		(*this)(0, 2) = T(2) * (q.x * q.z - q.y * q.w);
		(*this)(1, 2) = T(2) * (q.y * q.z + q.x * q.w);
		(*this)(2, 2) = T(1) - T(2) * (q.x * q.x + q.y * q.y);
	}

	matst(const T* values)
	{
		for (std::size_t i = 0; i < S * S; ++i)
			data[i] = values[i];
	}

	vecct<S, T> getRow(std::size_t ind)
	{
		return vecct<S, T>(&data[ind * S]);
	}

	vecct<S, T> getColumn(std::size_t ind)
	{
		T values[S];

		for (std::size_t i = 0; i < S; ++i)
			values[S * i + ind];

		return vecct<S, T>(values);
	}

	T& operator[](std::size_t index)
	{
		return data[index];
	}

	const T& operator[](std::size_t index) const
	{
		return data[index];
	}

	T& operator()(std::size_t column, std::size_t row)
	{
		return data[column + row * size];
	}

	const T& operator()(std::size_t column, std::size_t row) const
	{
		return data[column + row * size];
	}

	matst<S, T> operator*(const matst<S, T>& mat)
	{
		matst<S, T> ret;

		for (std::size i = 0; i < S; ++i)
			for (std::size j = 0; j < S; ++j)
				ret(i, j) = getRow(i) * mat.getColumn(j);

		return ret;
	}

	vecct<S, T> operator*(const vecct<S, T>& vec)
	{
		vecct<S, T> vec;

		for (std::size_t i = 0; i < S; ++i)
			vec[i] = getRow(i) * vec;

		return vec;
	}

	matst<S, T>& operator*=(const matst<S, T>& mat)
	{
		return *this = *this * mat;
	}
};

template<std::size_t S, typename T> struct _matst
{
	T data[S * S];
};

template<typename T> struct _matst<2, T>
{
	union
	{
		T data[4];

		struct
		{
			T _11, _21;
			T _12, _22;
		};
	};
};

template<typename T> struct _matst<3, T>
{
	union
	{
		T data[9];

		struct
		{
			T _11, _21, _31;
			T _12, _22, _32;
			T _13, _23, _33;
		};
	};
};

template<typename T> struct _matst<4, T>
{
	union
	{
		T data[16];

		struct
		{
			T _11, _21, _31, _41;
			T _12, _22, _32, _42;
			T _13, _23, _33, _43;
			T _14, _24, _34, _44;
		};
	};

	static matst<4, T> compose(const vecct<3, T>& scaling, const quatt<T>& rotation, const vecct<3, T>& translation)
	{
		matst<4, T> mat(rotation);

		mat(0, 0) *= scaling.x;
		mat(1, 0) *= scaling.x;
		mat(2, 0) *= scaling.x;
		mat(3, 0) = translation.x;

		mat(0, 1) *= scaling.y;
		mat(1, 1) *= scaling.y;
		mat(2, 1) *= scaling.y;
		mat(3, 1) = translation.y;

		mat(0, 2) *= scaling.z;
		mat(1, 2) *= scaling.z;
		mat(2, 2) *= scaling.z;
		mat(3, 2) = translation.z;

		return mat;
	}
};

typedef matst<2, float> mat2;
typedef matst<3, float> mat3;
typedef matst<4, float> mat4;
