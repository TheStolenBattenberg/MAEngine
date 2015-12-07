#pragma once

#include <vector>

#include "Types.h"
#include "Memory.h"

class Buffer
{
public:
	Buffer(Memory* data);
	~Buffer();

	void reserve(uint amount);
	void remove(uint offset, uint length);
	void seek(uint pos);
	uint tell();
	uint size();
	const void* get();

	void write(const void* data, uint length);
	void read(void* data, uint length);
	void poke(uint offset, const void* data, uint length);
	void peek(uint offset, void* data, uint length);

	template<typename T> inline void write(T val)
	{
		write(&val, sizeof(val));
	}

	template<typename T> inline T read()
	{
		T val;
		read(&val, sizeof(val));
		return val;
	}

	template<typename T> inline void poke(uint offset, T value)
	{
		poke(offset, &value, sizeof(value));
	}

	template<typename T> inline T peek(uint offset)
	{
		T val;
		peek(offset, &val, sizeof(val));
		return val;
	}

private:
	Memory* data;

	uint pos = 0;
};
