#pragma once

#include <MAE/Core/Releasable.h>

class Renderer: public Releasable {
public:
	virtual void release() = 0;
};
