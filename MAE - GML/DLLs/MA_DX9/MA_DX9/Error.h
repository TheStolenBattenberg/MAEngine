#pragma once

#include "Types.h"

#include <string>
#include <stack>
#include <d3d9.h>
#include <vector>

enum ErrorCode: long
{
	ErrorOk                  =  0x01,
	ErrorD3D9                = -0x01, // DataD3D9, DataFunction
	ErrorInv                 = -0x02,
	ErrorReadFile            = -0x03, // DataFile
	ErrorCreateVertexBuffer  = -0x04, // DataD3D9
	ErrorCreateIndexBuffer   = -0x05, // DataD3D9
	ErrorCreateVertexDecl    = -0x06, // DataD3D9
	ErrorCompileVertexShader = -0x07, // DataD3D9, DataShader
	ErrorCreateVertexShader  = -0x08, // DataD3D9
	ErrorCompilePixelShader  = -0x09, // DataD3D9, DataShader
	ErrorCreatePixelShader   = -0x0A, // DataD3D9
	ErrorCreateTexture       = -0x0B, // DataD3D9
	ErrorCreateTexFromFile   = -0x0C  // DataD3D9, DataTexFile
};

class ErrorObject
{
public:
	class DataEntry
	{
	public:
		DataEntry(uint value): num(value) { }
		DataEntry(std::string value): str(value) { }

		uint num = 0;
		std::string str = "";
	};

	enum DataIndex: uint
	{
		DataD3D9     = 0,
		DataFunction = 1,
		DataShader   = 1,
		DataFile     = 0,
		DataTexFile  = 1,
	};

	ErrorObject(): code(ErrorOk) { };
	template<typename... Args> ErrorObject(ErrorCode code, Args... args): code(code), data{DataEntry(args)...} { }

	ErrorCode getCode() const;

	uint getNumber(DataIndex ind) const;
	std::string getString(DataIndex ind) const;

	std::string getErrorString() const;

	static std::string getError(ErrorCode code);
	static std::string getErrorD3D9(HRESULT code);

private:
	ErrorCode code;

	std::vector<DataEntry> data;
};

class CriticalErrorHandler
{
public:
	enum
	{
		ShowMessage      = 0x01,
		ShowDebugMessage = 0x02,
		PushToStack      = 0x04
	};

	void onError(const ErrorObject& err);
	bool empty();
	ErrorObject pop();

	uint flags;

private:
	const uint maxStack = 0x10;

	std::stack<ErrorObject> errorStack;
};

template<typename... Args> inline ErrorCode ErrorHandle(ErrorObject& err, ErrorCode code, Args... args)
{
	err = ErrorObject(code, args...);

	return code;
}

template<typename... Args> inline ErrorCode ErrorHandleCritical(ErrorObject& err, CriticalErrorHandler& handler, ErrorCode code, Args... args)
{
	err = ErrorObject(code, args...);

	handler.onError(err);

	return code;
}
