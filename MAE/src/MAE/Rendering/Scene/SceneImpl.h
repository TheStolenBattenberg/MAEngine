#pragma once

#include <MAE/Rendering/Scene/Scene.h>
#include <MAE/Rendering/Scene/Entity.h>

#include <list>

class SceneImpl: public Scene {
public:
	~SceneImpl();

	void release();

	Entity* createEntity();
};
