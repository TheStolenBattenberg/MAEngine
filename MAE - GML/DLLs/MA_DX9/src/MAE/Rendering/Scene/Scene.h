#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/RefCounted.h>

class Scene: public RefCounted {
public:
	virtual uint release() = 0;

	virtual ErrorCode createEntity(class Entity*& entity) = 0;
};
