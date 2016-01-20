#pragma once

#include "Types.h"
#include "Error.h"

#include <vector>
#include <fstream>
#include <algorithm>

template<typename T> inline T clamp(T value, T min, T max) {
	return std::min(std::max(value, min), max);
}

template<typename T> inline bool isValidIndex(uint ind, std::vector<T*>& vec)
{
	if (ind >= vec.size())
		return 0;

	if (vec[ind] == 0)
		return 0;

	return 1;
}

template<typename T> uint putInto(T* value, std::vector<T*>& vec)
{
	for (uint i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == 0)
		{
			vec[i] = value;
			return i;
		}
	}

	uint ind = vec.size();

	vec.push_back(value);

	return ind;
}

template<typename T> inline void ClearVector(std::vector<T*>& vec)
{
	for (auto i: vec)
		if (i != 0)
			delete i;

	vec.clear();
}

template<typename T> inline bool ReadFromFile(std::ifstream& f, T& val)
{
	return f.read((char*) &val, sizeof(val)) ? 1 : 0;
}

inline double PtrToDouble(void* value)
{
	static_assert(sizeof(double) >= sizeof(void*), "Size of double must be greater or equal to the size of void*");

	double r = 0.0;

	*(void**) &r = value;

	return r;
}

inline void* DoubleToPtr(double value)
{
	static_assert(sizeof(double) >= sizeof(void*), "Size of double must be greater or equal to the size of void*");

	return *(void**) &value;
}

template<typename... Args> inline ErrorCode ErrorHandle(ErrorObject& err, ErrorCode code, Args... args)
{
	err = ErrorObject(code, args...);

	return code;
}

template<typename... Args> inline ErrorCode ErrorHandleCritical(ErrorObject& err, CriticalErrorHandler& handler, ErrorCode code, Args... args)
{
	err = ErrorObject(code, args...);

	handler.onError(err);

	return code;
}

template<typename T> inline T* VectorGetPointerSafe(uint index, const std::vector<T*>& vec)
{
	return index >= surfaces.size() ? 0 : surfaces[index];
}

template<typename T> inline uint VectorPushBackPointer(T* ptr, std::vector<T*>& vec)
{
	auto it = std::find(vec.begin(), vec.end(), (T*) 0);

	if (it == vec.end())
	{
		vec.push_back(ptr);
		return vec.size() - 1;
	}

	*it = ptr;
	return it - vec.begin();
}
