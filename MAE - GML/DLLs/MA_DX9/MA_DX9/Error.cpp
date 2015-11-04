#define _CRT_SECURE_NO_WARNINGS

#include "Error.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

void Error::onError(std::string s) {
	if (flags & ErrorShowMessage)
		MessageBox(0, s.c_str(), "MA_DX9", MB_OK | MB_ICONERROR);

	if (flags & ErrorShowDebugMessage) {
		std::cout << s << std::endl;
		std::cout.flush();
	}

	if (flags & ErrorPushToStack)
		if (errorStack.size() < maxStack)
			errorStack.push(s);
}

bool Error::empty() {
	return errorStack.empty();
}

std::string Error::pop() {
	std::string s;

	if (errorStack.empty())
		s = "No error occurd";
	else {
		s = errorStack.top();
		errorStack.pop();
	}

	return s;
}

#ifndef NODX9ERR
	#include <DxErr.h>
	#pragma comment(lib, "dxerr.lib")

	int(_cdecl *__vsnprintf)(char*, size_t, const char*, va_list) = _vsnprintf;

	void Error::onErrorDX9(std::string s, long res) {
		onError(s + " (" + DXGetErrorString(res) + ")");
	}
#else
	void Error::onErrorDX9(std::string s, long res) {
		onError(s);
	}
#endif