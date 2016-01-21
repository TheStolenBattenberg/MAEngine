#include "Error.h"

const char* ErrorCodeGetString(ErrorCode code)
{
	switch (code)
	{
	case ErrorOk:
		return "No error occurd";
	case ErrorD3D9:
		return "A DirectX9 error occurd";
	case ErrorInv:
		return "Invalid parameters";
	case ErrorReadFile:
		return "Failed to read from file";
	case ErrorCreateVertexBuffer:
		return "Failed to create vertex buffer";
	case ErrorCreateIndexBuffer:
		return "Failed to create index buffer";
	case ErrorCreateVertexDecl:
		return "Failed to create vertex declaration";
	case ErrorCompileVertexShader:
		return "Failed to compile vertex shader";
	case ErrorCreateVertexShader:
		return "Failed to create vertex shader";
	case ErrorCompilePixelShader:
		return "Failed to compile pixel shader";
	case ErrorCreatePixelShader:
		return "Failed to create pixel shader";
	case ErrorCreateTexture:
		return "Failed to create texture";
	case ErrorCreateSurface:
		return "Failed to create surface";
	case ErrorMemory:
		return "Failed to allocate memory";
	}

	return "Invalid error code";
}
