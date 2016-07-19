#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/Types.h>

class IndexBuffer: public Deletable {
public:
	enum {
		MapWrite = 0x01,
		MapRead  = 0x02
	};

	virtual ~IndexBuffer() { };

	template<typename T> T* map(uint offset, uint size, uint flags) {
		return (T*) map(offset, size, flags);
	}

	virtual void* map(uint offset, uint size, uint flags) = 0;
	virtual void unmap() = 0;
	virtual void upload(const void* data, uint offset, uint size) = 0;
};
