#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/Releasable.h>

#include <Mat.h>

class Entity: public Releasable {
public:
	virtual void release() = 0;

	virtual ErrorCode setModel(class Model* model) = 0;
	virtual ErrorCode setTransformation(const mat4& mat) = 0;
};
