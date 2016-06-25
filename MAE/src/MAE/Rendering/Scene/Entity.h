#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/RefCounted.h>

#include <Mat.h>

class Entity: public RefCounted {
public:
	virtual uint release() = 0;

	virtual ErrorCode setModel(class Model* model) = 0;
	virtual ErrorCode setTransformation(const mat4& mat) = 0;
};
