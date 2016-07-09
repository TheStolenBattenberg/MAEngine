#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class VertexData: public Releasable {
public:
	enum {
		TypeFloat = 0,
		TypeVec2  = 1,
		TypeVec3  = 2,
		TypeVec4  = 3,
		TypeMax   = 4
	};

	virtual void release() = 0;

	inline uint getIndexDX9(uint usage, uint index) {
		return (index << 16) | usage;
	}

	virtual void setVertexBuffer(class VertexBuffer* vb, uint offset, uint stride);
	virtual void addElement(uint index, uint type, uint offset);
};
