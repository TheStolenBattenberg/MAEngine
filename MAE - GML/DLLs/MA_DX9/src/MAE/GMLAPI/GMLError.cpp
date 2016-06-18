#include <MAE/Main.h>
#include <MAE/GMLAPI/GMLMain.h>

#include <iostream>
#include <stack>

enum ErrorFlags: uint
{
	ErrorFlagPush   = 0x01,
	ErrorFlagDbgMsg = 0x02,
	ErrorFlagMsg    = 0x04
};

static std::stack<ErrorCode> errorCodes;

static uint curFlags;
static bool isSet = 0;

DLLEXPORT double MAE_ErrorSetFlags(double flags)
{
	if ((curFlags = (uint) flags) != 0 && !isSet)
	{
		mamain->onError([](ErrorCode code) {
			if (curFlags & ErrorFlagPush)
				errorCodes.push(code);

			if (curFlags & ErrorFlagDbgMsg)
				std::cout << "[MAE] " << ErrorCodeGetString(code) << std::endl;

			if (curFlags & ErrorFlagMsg)
				MessageBox(0, ErrorCodeGetString(code), "MAE - Engine", MB_OK | MB_ICONERROR);
		});

		isSet = 1;
	}

	return ErrorOk;
}

DLLEXPORT double MAE_ErrorPop()
{
	if (errorCodes.empty())
		return ErrorOk;

	ErrorCode c = errorCodes.top();
	errorCodes.pop();

	return c;
}

DLLEXPORT const char* MAE_ErrorGetString(double code)
{
	return ErrorCodeGetString((ErrorCode) (int) code);
}
