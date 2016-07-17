#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class VertexData: public Releasable {
public:
	virtual void release() = 0;
};
