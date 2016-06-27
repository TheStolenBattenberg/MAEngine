#include <MAE/Rendering/Scene/EntityImpl.h>
#include <MAE/Rendering/Scene/SceneImpl.h>

EntityImpl::~EntityImpl() {
	main->removeEntity(this);
}

void EntityImpl::release() {
	::delete this;
}

ErrorCode EntityImpl::setModel(class Model* model) {
	this->model = model;

	return ErrorOk;
}

ErrorCode EntityImpl::setTransformation(const mat4& mat) {
	this->mat = mat;

	return ErrorOk;
}
