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
	// TODO: Add proper error checking
	data->reserve(amount);
}

void Buffer::remove(uint offset, uint length)
{
	// TODO: Add proper error checking
	data->remove(offset, length);

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
	// TODO: Add proper error checking

	if (pos > data->size())
		return;

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
	// TODO: Add proper error checking
	
	if (!this->data->write(pos, length, data))
		return;

	pos += length;
}

void Buffer::read(void* data, uint length)
{
	// TODO: Add proper error checking
	
	if (!this->data->read(pos, length, data))
		return;

	pos += length;
}

void Buffer::poke(uint offset, const void* data, uint length)
{
	// TODO: Add proper error checking

	this->data->write(offset, length, data);
}

void Buffer::peek(uint offset, void* data, uint length)
{
	// TODO: Add proper error checking

	this->data->read(offset, length, data);
}
