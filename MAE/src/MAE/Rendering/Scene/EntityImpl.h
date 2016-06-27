#pragma once

#include <MAE/Rendering/Scene/Entity.h>

class EntityImpl: public Entity {
public:
	EntityImpl(class SceneImpl* main): main(main) { }
	~EntityImpl();

	void release();

	ErrorCode setModel(class Model* model);
	ErrorCode setTransformation(const mat4& mat);

private:
	class SceneImpl* main;

	class Model* model;
	mat4 mat;
};
