#pragma once

#include "Types.h"

#include <string>
#include <exception>
#include <stdexcept>

#define _GMEXBEG() \
	try            \
	{

#define _GMEXEND(ret, e, ignoreInv) \
	}                               \
	catch (MAEInvException ex)      \
	{                               \
		if (!(ignoreInv))           \
			(e).onError(ex.what()); \
                                    \
		return (ret);               \
	}                               \
	catch (std::exception ex)       \
	{                               \
		(e).onError(ex.what());     \
		return (ret);               \
	}

#define _GMEXENDSIMPLE(ret)   \
	}                         \
	catch (std::exception ex) \
	{                         \
		return (ret);         \
	}


class MAEException: public std::runtime_error {
public:
	explicit MAEException(const std::string& msg): std::runtime_error(msg) { }
	explicit MAEException(const char* msg): std::runtime_error(msg) { }
};

class MAEInvException: public MAEException {
public:
	explicit MAEInvException(const std::string& msg): MAEException(msg) { }
	explicit MAEInvException(const char* msg): MAEException(msg) { }
};

class MAEDX9Exception: public MAEException
{
public:
	MAEDX9Exception(uint code, const std::string& msg): MAEException(format(code, msg)) { }

private:
	static std::string format(uint code, const std::string& msg);
};
