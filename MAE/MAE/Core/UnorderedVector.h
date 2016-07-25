#pragma once

#include <assert.h>
#include <vector>

template<class T> class UnorderedVector {
public:
	auto begin() {
		return data.begin();
	}

	auto begin() const {
		return data.begin();
	}

	auto end() {
		return data.end();
	}

	auto end() const {
		return data.end();
	}

	auto size() const {
		return data.size();
	}

	void add(const T& val) {
		data.push_back(val);
	}

	void remove(const T& val) {
		assert(("Element was not found", data.size() != 0));

		if (*(data.end() - 1) == val) {
			data.pop_back();
			return;
		}

		for (auto& i : data) {
			if (i == val) {
				i = std::move(*(data.end() - 1));
				data.pop_back();
				return;
			}
		}

		assert("Element was not found");
	}

	void clear() {
		data.clear();
	}

private:
	std::vector<T> data;
};
