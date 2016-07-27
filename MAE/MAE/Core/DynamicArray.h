#pragma once

#include <MAE/Core/Types.h>

#include <algorithm>
#include <iterator>

template<typename T> class DynamicArray {
public:
	DynamicArray(): m_data(nullptr), m_size(0) { }

	DynamicArray(uint size): m_data(size != 0 ? new T[size] : nullptr), m_size(size) { }

	DynamicArray(uint size, const T* data): DynamicArray(size) {
		std::copy(data, data + size, m_data);
	}

	DynamicArray(const DynamicArray<T>& arr): DynamicArray(arr.m_size, arr.m_data) { }

	DynamicArray(DynamicArray<T>&& arr): m_data(arr.m_data), m_size(arr.m_size) {
		arr.m_data = nullptr;
		arr.m_size = 0;
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

	DynamicArray<T>& operator=(const DynamicArray<T>& arr) {
		if (m_size < arr.m_size) {
			delete[] m_data;
			m_data = new T[arr.m_size];
		}

		m_size = arr.m_size;
		std::copy(arr.begin(), arr.end(), begin());

		return *this;
	}

	DynamicArray<T>& operator=(DynamicArray<T>&& arr) {
		delete[] m_data;

		m_data = arr.m_data;
		m_size = arr.m_size;

		arr.m_data = nullptr;
		arr.m_size = 0;

		return *this;
	}

	DynamicArray<T> join(const DynamicArray<T>& other) const {
		DynamicArray<T> arr(m_size + other.m_size);

		// Copy data
		std::copy(begin(), end(), arr.m_data);
		std::copy(other.begin(), other.end(), arr.m_data + m_size);

		return arr;
	}

	void size(uint newsize) {
		if (m_size == newsize)
			return;

		if (newsize == 0) {
			delete[] m_data;
			m_data = nullptr;
			m_size = 0;
			return;
		}

		if (m_size == 0) {
			m_data = new T[newsize];
			m_size = newsize;
			return;
		}

		auto arr = std::copy(begin(), end(), new T[newsize]);
		delete[] m_data;

		m_data = arr;
		m_size = newsize;
	}

	inline bool empty() const {
		return m_size == 0;
	}

	inline uint size() const {
		return m_size;
	}

	inline T* data() {
		return m_data;
	}

	inline const T* data() const {
		return m_data;
	}

private:
	T* m_data;
	uint m_size;
};
