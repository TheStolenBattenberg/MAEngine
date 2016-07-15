#pragma once

#include <MAE/Rendering/Scene/Scene.h>

#include <list>

class SceneImpl: public Scene {
public:
	~SceneImpl();

	void release();

	class Entity* createEntity();
};
