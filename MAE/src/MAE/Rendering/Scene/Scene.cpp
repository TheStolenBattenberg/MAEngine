#include <MAE/Rendering/Scene/EntityImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>
#include <MAE/MainImpl.h>

SceneImpl::~SceneImpl() {

}

void SceneImpl::release() {
	::delete this;
}

Entity* SceneImpl::createEntity() {
	return ::new EntityImpl();
}
