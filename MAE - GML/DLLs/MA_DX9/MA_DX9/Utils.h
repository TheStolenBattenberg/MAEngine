#pragma once

#include <vector>

#include "Types.h"

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
