#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/Releasable.h>

class Scene: public Releasable {
public:
	virtual void release() = 0;

	virtual ErrorCode createEntity(class Entity*& entity) = 0;
};
