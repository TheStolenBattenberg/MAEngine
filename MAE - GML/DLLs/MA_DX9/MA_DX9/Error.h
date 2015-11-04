#pragma once

#include "Types.h"

#include <string>
#include <stack>

enum {
	ErrorShowMessage      = 0x01,
	ErrorShowDebugMessage = 0x02,
	ErrorPushToStack      = 0x04
};

class Error {
public:
	void onError(std::string s);
	void onErrorDX9(std::string s, long res);
	bool empty();
	std::string pop();

	uint flags;

private:
	const uint maxStack = 0x10;

	std::stack<std::string> errorStack;
};