#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/Types.h>

class VertexDataBuilder: public Deletable {
public:
	enum {
		TypeFloat = 0,
		TypeVec2  = 1,
		TypeVec3  = 2,
		TypeVec4  = 3
	};

	virtual ~VertexDataBuilder() { }

	virtual void setIndexBuffer(class IndexBuffer* ib) = 0;
	virtual void setVertexBuffer(class VertexBuffer* vb, uint offset, uint stride) = 0;
	virtual void addElement(uint location, uint type, uint offset) = 0;
};
