#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class Renderer: public Releasable {
public:
	virtual void release() = 0;

	virtual class VertexBuffer* createVertexBuffer(uint length) = 0;
};
