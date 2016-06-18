#pragma once

#include <MAE/Core/Types.h>

class RefCounted {
public:
	uint addRef() {
		return ++count;
	}

	virtual uint release() = 0;

protected:
	uint count = 1;
};
