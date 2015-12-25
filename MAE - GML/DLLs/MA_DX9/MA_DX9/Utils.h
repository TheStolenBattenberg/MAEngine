#pragma once

#include <vector>
#include <fstream>
#include <algorithm>

#include "Types.h"



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

template<typename T> inline void ReadFromFile(std::ifstream& f, T& val)
{
	f.read((char*) &val, sizeof(val));

	// TODO: Add error handling
}

template<typename T> inline T ReadFromFile(std::ifstream& f)
{
	T ret;

	ReadFromFile(f, ret);

	return ret;
}

template<typename T> inline void ReadVectorFromFile(std::ifstream& f, std::vector<T>& vec, uint items)
{
	vec.reserve(items);

	for (uint i = 0; i < items; ++i)
		vec.push_back(ReadFromFile<T>(f));
}
