#include <MAE/Rendering/Scene/EntityImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>
#include <MAE/MainImpl.h>

SceneImpl::~SceneImpl() {
	while (!entities.empty())
		delete entities.front();
}

void SceneImpl::release() {
	::delete this;
}

ErrorCode SceneImpl::createEntity(Entity*& entity) {
	EntityImpl* e = ::new(std::nothrow) EntityImpl(this);

	if (e == 0)
		return main->setError(ErrorMemory);

	entities.push_back(e);
	entity = (Entity*) e;

	return ErrorOk;
}

void SceneImpl::removeEntity(Entity* entity) {
	entities.remove_if([entity](Entity* en) { return en == entity; });
}
