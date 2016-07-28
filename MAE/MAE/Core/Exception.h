#pragma once

#include <stdexcept>

class Exception: public std::runtime_error {
public:
	explicit Exception(const std::string& msg): std::runtime_error(msg) { }
	explicit Exception(const char* msg): std::runtime_error(msg) { }
};
