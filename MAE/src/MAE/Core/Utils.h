#pragma once

#include <istream>

template<typename _Elem, typename _Traits, typename T> inline bool readFromStream(std::basic_istream<_Elem, _Traits>& stream, T& val) {
	return stream.read((_Elem*) &val, sizeof(val)) ? 1 : 0;
}

template<typename T> inline void freeContainer(T& container) {
	for (auto i : container)
		delete i;
}
