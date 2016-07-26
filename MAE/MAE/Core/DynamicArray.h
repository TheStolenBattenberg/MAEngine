#pragma once

#include <MAE/Core/Types.h>

#include <algorithm>
#include <iterator>

template<typename T> class DynamicArray {
public:
	DynamicArray(uint size): m_size(size), m_data(new T[size]) { }

	DynamicArray(uint size, const T* data): m_size(size), m_data(new T[size]) {
		std::copy(data, data + size, m_data);
	}

	DynamicArray(const DynamicArray& arr): m_size(arr.m_size), m_data(new T[arr.m_size]) {
		std::copy(arr.begin(), arr.end(), m_data);
	}

	~DynamicArray() {
		delete[] m_data;
	}

	inline T* begin() {
		return m_data;
	}

	inline const T* begin() const {
		return m_data;
	}

	inline T* end() {
		return m_data + m_size;
	}

	inline const T* end() const {
		return m_data + m_size;
	}

	inline T& operator[](uint ind) {
		return m_data[ind];
	}

	inline const T& operator[](uint ind) const {
		return m_data[ind];
	}

	DynamicArray<T> join(const DynamicArray<T>& other) const {
		DynamicArray arr(m_size + other.m_size);

		// Copy data
		std::copy(begin(), end(), arr.m_data);
		std::copy(other.begin(), other.end(), arr.m_data + m_size);

		return arr;
	}

	inline uint size() const {
		return m_size;
	}

	inline T* data() const {
		return m_data;
	}

private:
	T* m_data;
	uint m_size;
};
