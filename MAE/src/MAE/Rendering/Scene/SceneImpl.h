#pragma once

#include <MAE/Rendering/Scene/Scene.h>

#include <list>

class SceneImpl: public Scene {
public:
	SceneImpl(class MainImpl* main): main(main) { };
	~SceneImpl();

	void release();

	class Entity* createEntity();

private:
	class MainImpl* main;
};
