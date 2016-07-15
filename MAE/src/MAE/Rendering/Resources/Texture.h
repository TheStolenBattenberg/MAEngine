#pragma once

#include <MAE/Core/Types.h>
#include <MAE/Core/Releasable.h>

#include <string>

class Texture: public Releasable {
public:
	virtual void release() = 0;
};
