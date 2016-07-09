#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class Renderer: public Releasable {
public:
	virtual void release() = 0;

	virtual class VertexBuffer* createVertexBuffer(uint length) = 0;
	virtual class VertexData* createVertexData() = 0;
	virtual void buildVertexData(class VertexData* vd) = 0;
	virtual void setVertexData(class VertexData* vd) = 0;
};
