#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

#include <Mat.h>

class Entity: public Releasable {
public:
	virtual void release() = 0;
};
