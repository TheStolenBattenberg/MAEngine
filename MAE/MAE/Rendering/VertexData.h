#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/Types.h>

class VertexData: public Deletable {
public:
	enum {
		TypeFloat = 0,
		TypeVec2  = 1,
		TypeVec3  = 2,
		TypeVec4  = 3
	};

	enum {
		SetVertexBuffer = 0x01,
		SetStride       = 0x02,
		SetOffset       = 0x04,
		SetElements     = 0x08
	};

	struct Element {
		uint m_location;
		uint m_type;
		uint m_offset;
	};

	virtual ~VertexData() { }

	virtual uint addVertexBuffer(class VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements) = 0;
	virtual void build() = 0;
	virtual void clear() = 0;
	virtual void removeVertexBuffer(uint id) = 0;
	virtual void setIndexBuffer(class IndexBuffer* ib) = 0;
	virtual void setVertexBuffer(uint id, uint flags, class VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements) = 0;
};
