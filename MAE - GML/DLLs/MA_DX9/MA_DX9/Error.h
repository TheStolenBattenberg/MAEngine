#pragma once

#include <string>
#include <stack>

#include "Types.h"

class Error
{
public:
	enum
	{
		ShowMessage      = 0x01,
		ShowDebugMessage = 0x02,
		PushToStack      = 0x04
	};

	void onError(std::string s);
	void onErrorDX9(std::string s, long res);
	bool empty();
	std::string pop();

	uint flags;

private:
	const uint maxStack = 0x10;

	std::stack<std::string> errorStack;
};
