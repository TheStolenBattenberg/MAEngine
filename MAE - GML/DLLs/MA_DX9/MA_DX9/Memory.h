#pragma once

#include "Types.h"

#include <vector>

typedef void(*UnlockMemFunc)(void* obj);

class Memory
{
public:
	virtual bool read(uint offset, uint length, void* dest) = 0;
	virtual bool write(uint offset, uint length, const void* src) = 0;
	virtual bool reserve(uint amount) = 0;
	virtual bool remove(uint offset, uint length) = 0;
	virtual const void* get() = 0;
	virtual uint size() = 0;
};

class FixedMemory: public Memory
{
public:
	enum
	{
		FlagReadOnly  = 0x01,
		FlagWriteOnly = 0x02
	};

	FixedMemory(void* obj, UnlockMemFunc func, void* ptr, uint length, uint flags);
	~FixedMemory();
	bool read(uint offset, uint length, void* dest);
	bool write(uint offset, uint length, const void* src);
	bool reserve(uint amount);
	bool remove(uint offset, uint length);
	const void* get();
	uint size();

private:
	void* obj;
	void* ptr;
	uint  length;
	uint  flags;

	UnlockMemFunc func;
};

class DynamicMemory
{
public:
	bool read(uint offset, uint length, void* dest);
	bool write(uint offset, uint length, const void* src);
	bool reserve(uint amount);
	bool remove(uint offset, uint length);
	const void* get();
	uint size();

private:
	std::vector<ubyte> data;
};
