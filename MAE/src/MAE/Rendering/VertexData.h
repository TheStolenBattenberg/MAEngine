#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/Types.h>

class VertexData: public Deletable {
public:
	virtual ~VertexData() { };

	virtual void replaceVertexBuffer(class VertexBuffer* old, class VertexBuffer* replacement) = 0;
	virtual void setIndexBuffer(class IndexBuffer* ib) = 0;
};
