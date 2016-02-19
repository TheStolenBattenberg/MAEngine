#pragma once

#include "Entity.h"

class EntityImpl: public Entity {
public:
	EntityImpl(class SceneImpl* main): main(main) { }
	~EntityImpl();

	virtual uint release();

	virtual ErrorCode setModel(class Model* model);
	virtual ErrorCode setTransformation(const mat4& mat);

private:
	class SceneImpl* main;

	class Model* model;
	mat4 mat;
};
