#include "EntityImpl.h"
#include "SceneImpl.h"
#include "MainImpl.h"

SceneImpl::~SceneImpl() {
	while (!entities.empty())
		delete entities.front();
}

uint SceneImpl::release() {
	if (--count == 0)
		delete this;

	return count;
}

ErrorCode SceneImpl::createEntity(Entity*& entity) {
	EntityImpl* e = new(std::nothrow) EntityImpl(this);

	if (e == 0)
		return main->setError(ErrorMemory);

	entities.push_back(e);
	entity = (Entity*) e;

	return ErrorOk;
}

void SceneImpl::removeEntity(Entity* entity) {
	entities.remove_if([entity](Entity* en) { return en == entity; });
}
