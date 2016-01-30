#pragma once

#include "Types.h"

class RefCounted {
public:
	uint addRef() {
		return ++count;
	}

	virtual uint release() = 0;

protected:
	uint count = 1;
};
