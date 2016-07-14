#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class Scene: public Releasable {
public:
	virtual void release() = 0;

	virtual class Entity* createEntity() = 0;
};
