#include "Error.h"

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>

ErrorCode ErrorObject::getCode() const
{
	return code;
}

uint ErrorObject::getNumber(DataIndex ind) const
{
	if (ind >= data.size())
		return 0;

	return data[ind].num;
}

std::string ErrorObject::getString(DataIndex ind) const
{
	if (ind >= data.size())
		return "";

	return data[ind].str;
}

std::string ErrorObject::getErrorString() const
{
	std::stringstream ss;

	ss << getError(code);

	switch (code)
	{
	case ErrorD3D9:
		ss << " (" << getString(DataFunction) << ")" << std::endl << getErrorD3D9(getNumber(DataD3D9));
		break;
	case ErrorCreateVertexBuffer:
	case ErrorCreateIndexBuffer:
	case ErrorCreateVertexDecl:
	case ErrorCreateVertexShader:
	case ErrorCreatePixelShader:
	case ErrorCreateTexture:
		ss << std::endl << getErrorD3D9(getNumber(DataD3D9));
		break;
	case ErrorReadFile:
		ss << " (" << getString(DataFile) << ")";
		break;
	case ErrorCompileVertexShader:
	case ErrorCompilePixelShader:
		ss << std::endl << "D3D9 Error: " << getErrorD3D9(getNumber(DataD3D9))
		   << std::endl << "Shader Error: " << getString(DataShader);
		break;
	case ErrorCreateTexFromFile:
		ss << " (" << getString(DataTexFile) << ")" << std::endl << getErrorD3D9(getNumber(DataD3D9));
		break;
	}

	return ss.str();
}

std::string ErrorObject::getError(ErrorCode code)
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
	case ErrorCreateTexFromFile:
		return "Failed to create texture from file";
	case ErrorMemory:
		return "Failed to allocate memory";
	}

	std::stringstream ss;

	ss << "Invalid error code (0x"
	   << std::setfill('0')
	   << std::setw(sizeof(code) * 2)
	   << std::hex
	   << code
	   << ')';

	return ss.str();
}

std::string ErrorObject::getErrorD3D9(HRESULT code)
{
	switch (code)
	{
	case D3DOK_NOAUTOGEN:
		return "The call succeeded but there won't be any mipmaps generated (D3DOK_NOAUTOGEN)";
	case D3DERR_CONFLICTINGRENDERSTATE:
		return "Conflicting render state (D3DERR_CONFLICTINGRENDERSTATE)";
	case D3DERR_CONFLICTINGTEXTUREFILTER:
		return "Conflicting texture filter (D3DERR_CONFLICTINGTEXTUREFILTER)";
	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		return "Conflicting texture palette (D3DERR_CONFLICTINGTEXTUREPALETTE)";
	case D3DERR_DEVICEHUNG:
		return "Hardware adapter reset by OS (D3DERR_DEVICEHUNG)";
	case D3DERR_DEVICELOST:
		return "Device lost (D3DERR_DEVICELOST)";
	case D3DERR_DEVICENOTRESET:
		return "Device not reset (D3DERR_DEVICENOTRESET)";
	case D3DERR_DEVICEREMOVED:
		return "Hardware device was removed (D3DERR_DEVICEREMOVED)";
	case D3DERR_DRIVERINTERNALERROR:
		return "Driver internal error (D3DERR_DRIVERINTERNALERROR)";
	case D3DERR_DRIVERINVALIDCALL:
		return "Driver invalid call (D3DERR_DRIVERINVALIDCALL)";
	case D3DERR_INVALIDCALL:
		return "Invalid call (D3DERR_INVALIDCALL)";
	case D3DERR_INVALIDDEVICE:
		return "Invalid device (D3DERR_INVALIDDEVICE)";
	case D3DERR_MOREDATA:
		return "More data (D3DERR_MOREDATA)";
	case D3DERR_NOTAVAILABLE:
		return "Not available (D3DERR_NOTAVAILABLE)";
	case D3DERR_NOTFOUND:
		return "Not found (D3DERR_NOTFOUND)";
	case S_OK:
		return "The function completed successfully (S_OK)";
	case D3DERR_OUTOFVIDEOMEMORY:
		return "Out of video memory (D3DERR_OUTOFVIDEOMEMORY)";
	case D3DERR_TOOMANYOPERATIONS:
		return "Too many operations (D3DERR_TOOMANYOPERATIONS)";
	case D3DERR_UNSUPPORTEDALPHAARG:
		return "Unsupported alpha arg (D3DERR_UNSUPPORTEDALPHAARG)";
	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		return "Unsupported alpha operation (D3DERR_UNSUPPORTEDALPHAOPERATION)";
	case D3DERR_UNSUPPORTEDCOLORARG:
		return "Unsupported color arg (D3DERR_UNSUPPORTEDCOLORARG)";
	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		return "Unsupported color operation (D3DERR_UNSUPPORTEDCOLOROPERATION)";
	case D3DERR_UNSUPPORTEDFACTORVALUE:
		return "Unsupported factor value (D3DERR_UNSUPPORTEDFACTORVALUE)";
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		return "Unsupported texture filter (D3DERR_UNSUPPORTEDTEXTUREFILTER)";
	case D3DERR_WASSTILLDRAWING:
		return "Was still drawing (D3DERR_WASSTILLDRAWING)";
	case D3DERR_WRONGTEXTUREFORMAT:
		return "Wrong texture format (D3DERR_WRONGTEXTUREFORMAT)";
	case E_FAIL:
		return "An undetermined error occurred (E_FAIL)";
	case E_INVALIDARG:
		return "An invalid parameter was passed to the returning function (E_INVALIDARG)";
	case E_NOINTERFACE:
		return "The requested COM interface is not available (E_NOINTERFACE)";
	case E_NOTIMPL:
		return "The function called is not supported at this time (E_NOTIMPL)";
	case E_OUTOFMEMORY:
		return "Ran out of memory (E_OUTOFMEMORY)";
	case S_NOT_RESIDENT:
		return "Resource not resident in memory (S_NOT_RESIDENT)";
	case S_RESIDENT_IN_SHARED_MEMORY:
		return "Resource resident in shared memory (S_RESIDENT_IN_SHARED_MEMORY)";
	case S_PRESENT_MODE_CHANGED:
		return "Desktop display mode has changed (S_PRESENT_MODE_CHANGED)";
	case S_PRESENT_OCCLUDED:
		return "Client window is occluded (minimized or other fullscreen) (S_PRESENT_OCCLUDED)";
	case D3DERR_UNSUPPORTEDOVERLAY:
		return "Overlay is not supported (D3DERR_UNSUPPORTEDOVERLAY)";
	case D3DERR_UNSUPPORTEDOVERLAYFORMAT:
		return "Overlay format is not supported (D3DERR_UNSUPPORTEDOVERLAYFORMAT)";
	case D3DERR_CANNOTPROTECTCONTENT:
		return "Contect protection not available (D3DERR_CANNOTPROTECTCONTENT)";
	case D3DERR_UNSUPPORTEDCRYPTO:
		return "Unsupported cryptographic system (D3DERR_UNSUPPORTEDCRYPTO)";
	case D3DERR_PRESENT_STATISTICS_DISJOINT:
		return "Presentation statistics are disjoint (D3DERR_PRESENT_STATISTICS_DISJOINT)";
	}

	std::stringstream ss;

	ss << "Invalid or not supported error code (0x"
	   << std::setfill('0')
	   << std::setw(sizeof(code) * 2)
	   << std::hex
	   << code
	   << ')';

	return ss.str();
}

void CriticalErrorHandler::onError(const ErrorObject& err)
{
	std::string s = err.getErrorString();

	if (flags & ShowMessage)
		MessageBox(0, s.c_str(), "MAE", MB_OK | MB_ICONERROR);

	if (flags & ShowDebugMessage)
	{
		std::cout << s << std::endl;
		std::cout.flush();
	}

	if (flags & PushToStack)
		if (errorStack.size() < maxStack)
			errorStack.push(err);
}

bool CriticalErrorHandler::empty() {
	return errorStack.empty();
}

ErrorObject CriticalErrorHandler::pop() {
	if (errorStack.empty())
		return ErrorObject(ErrorOk);
	
	ErrorObject obj = errorStack.top();
	errorStack.pop();

	return obj;
}
