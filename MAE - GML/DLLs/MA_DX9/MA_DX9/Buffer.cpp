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

void Buffer::reserve(uint amount)
{
	if (!data->reserve(amount))
		mamain->err.onError("Failed to reserve memory");
}

void Buffer::remove(uint offset, uint length)
{
	if (!data->remove(offset, length))
		mamain->err.onError("Failed to remove memory");

	if (offset < pos)
	{
		if (offset + length > pos)
			pos = offset;
		else
			pos -= length;
	}
}

void Buffer::seek(uint pos)
{
	if (pos > data->size())
	{
		mamain->err.onError("Failed to seek position");
		return;
	}

	this->pos = pos;
}

uint Buffer::tell()
{
	return pos;
}

uint Buffer::size()
{
	return data->size();
}

const void* Buffer::get()
{
	return data->get();
}

void Buffer::write(const void* data, uint length)
{
	if (!this->data->write(pos, length, data))
	{
		mamain->err.onError("Failed to write to memory");
		return;
	}

	pos += length;
}

void Buffer::read(void* data, uint length)
{
	if (!this->data->read(pos, length, data))
	{
		mamain->err.onError("Failed to read from memory");
		return;
	}

	pos += length;
}

void Buffer::poke(uint offset, const void* data, uint length)
{
	if (!this->data->write(offset, length, data))
		mamain->err.onError("Failed to write to memory");
}

void Buffer::peek(uint offset, void* data, uint length)
{
	if (!this->data->read(offset, length, data))
		mamain->err.onError("Failed to read from memory");
}
