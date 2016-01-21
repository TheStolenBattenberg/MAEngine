#pragma once

#include "Types.h"

enum ErrorCode: int
{
	ErrorOk                  =  0x01,
	ErrorD3D9                = -0x01,
	ErrorInv                 = -0x02,
	ErrorReadFile            = -0x03,
	ErrorCreateVertexBuffer  = -0x04,
	ErrorCreateIndexBuffer   = -0x05,
	ErrorCreateVertexDecl    = -0x06,
	ErrorCompileVertexShader = -0x07,
	ErrorCreateVertexShader  = -0x08,
	ErrorCompilePixelShader  = -0x09,
	ErrorCreatePixelShader   = -0x0A,
	ErrorCreateTexture       = -0x0B,
	ErrorCreateSurface       = -0x0C,
	ErrorMemory              = -0x0D
};

const char* ErrorCodeGetString(ErrorCode code);
