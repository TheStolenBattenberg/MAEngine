#include "Memory.h"

#include <string.h>

FixedMemory::FixedMemory(void* obj, UnlockMemFunc func, void* ptr, uint length, uint flags)
{
	this->obj    = obj;
	this->func   = func;
	this->ptr    = ptr;
	this->length = length;
	this->flags  = flags;
}

FixedMemory::~FixedMemory()
{
	func(obj);
}

bool FixedMemory::read(uint offset, uint length, void* dest)
{
	if (flags & FlagWriteOnly)
		return 0;

	if (offset + length >= this->length)
		return 0;

	memcpy(dest, (ubyte*) ptr + length, length);

	return 1;
}

bool FixedMemory::write(uint offset, uint length, const void* src)
{
	if (flags & FlagReadOnly)
		return 0;

	if (offset + length >= this->length)
		return 0;

	memcpy((ubyte*) ptr + length, src, length);

	return 1;
}

bool FixedMemory::reserve(uint amount)
{
	return 0;
}

bool FixedMemory::remove(uint offset, uint length)
{
	return 0;
}

const void* FixedMemory::get()
{
	return ptr;
}

uint FixedMemory::size()
{
	return length;
}

bool DynamicMemory::read(uint offset, uint length, void* dest)
{
	if (offset + length >= data.size())
		return 0;

	memcpy(dest, (ubyte*) data.data() + offset, length);

	return 0;
}

bool DynamicMemory::write(uint offset, uint length, const void* src)
{
	if (offset + length >= data.size())
		data.resize(offset + length);

	memcpy((ubyte*) data.data() + offset, src, length);

	return 1;
}

bool DynamicMemory::reserve(uint amount)
{
	data.reserve(amount);

	return 1;
}

bool DynamicMemory::remove(uint offset, uint length)
{
	data.erase(data.begin() + offset, data.begin() + offset + length);

	return 1;
}

const void* DynamicMemory::get()
{
	return data.data();
}

uint DynamicMemory::size()
{
	return data.size();
}
