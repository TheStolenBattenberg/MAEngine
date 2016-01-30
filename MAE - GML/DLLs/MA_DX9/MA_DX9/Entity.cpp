#include "EntityImpl.h"
#include "SceneImpl.h"

EntityImpl::~EntityImpl() {
	main->removeEntity(this);
}

uint EntityImpl::release() {
	if (--count == 0)
		delete this;

	return count;
}

ErrorCode EntityImpl::setModel(class Model* model) {
	this->model = model;

	return ErrorOk;
}

ErrorCode EntityImpl::setTransformation(const mat4& mat) {
	this->mat = mat;

	return ErrorOk;
}
