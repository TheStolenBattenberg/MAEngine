#include <MAE/Rendering/Scene/EntityImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>

EntityImpl::~EntityImpl() {
	
}

void EntityImpl::release() {
	::delete this;
}
