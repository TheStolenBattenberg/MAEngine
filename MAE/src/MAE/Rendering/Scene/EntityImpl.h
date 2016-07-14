#pragma once

#include <MAE/Rendering/Scene/Entity.h>

class EntityImpl: public Entity {
public:
	~EntityImpl();

	void release();
};
