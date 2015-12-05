#include "Buffer.h"
#include "Main.h"

Buffer::Buffer(Memory* data)
{
	this->data = data;
}

Buffer::~Buffer()
{
	if (data != 0)
		delete data;
}

inline void Buffer::reserve(uint amount)
{
	if (!data->reserve(amount))
		mamain->err.onError("Failed to reserve memory");
}

inline void Buffer::remove(uint offset, uint length)
{
	if (!data->remove(offset, length))
		mamain->err.onError("Failed to remove memory");
}

inline void Buffer::seek(uint pos)
{
	if (pos > data->size())
	{
		mamain->err.onError("Failed to seek position");
		return;
	}

	this->pos = pos;
}

inline uint Buffer::tell()
{
	return pos;
}

inline uint Buffer::size()
{
	return data->size();
}

inline const void* Buffer::get()
{
	return data->get();
}

inline void Buffer::write(const void* data, uint length)
{
	if (!this->data->write(pos, length, data))
	{
		mamain->err.onError("Failed to write to memory");
		return;
	}

	pos += length;
}

inline void Buffer::read(void* data, uint length)
{
	if (!this->data->read(pos, length, data))
	{
		mamain->err.onError("Failed to read from memory");
		return;
	}

	pos += length;
}

inline void Buffer::poke(uint offset, const void* data, uint length)
{
	if (!this->data->write(offset, length, data))
		mamain->err.onError("Failed to write to memory");
}

inline void Buffer::peek(uint offset, void* data, uint length)
{
	if (!this->data->read(offset, length, data))
		mamain->err.onError("Failed to read from memory");
}
