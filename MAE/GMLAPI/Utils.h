#pragma once

template<typename T> inline double ptrToDouble(T* value) {
	static_assert(sizeof(double) >= sizeof(T*), "Size of double must be greater or equal to the size of void*");

	double r;

	*(T**) &r = value;

	return r;
}

template<typename T> inline T* doubleToPtr(double value) {
	static_assert(sizeof(double) >= sizeof(T*), "Size of double must be greater or equal to the size of void*");

	return *(T**) &value;
}
