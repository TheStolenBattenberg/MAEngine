#pragma once

#include <vector>

#include "Types.h"
#include "Memory.h"

class Buffer
{
public:
	Buffer(Memory* data);
	~Buffer();

	inline void reserve(uint amount);
	inline void remove(uint offset, uint length);
	inline void seek(uint pos);
	inline uint tell();
	inline uint size();
	inline const void* get();

	inline void write(const void* data, uint length);
	inline void read(void* data, uint length);
	inline void poke(uint offset, const void* data, uint length);
	inline void peek(uint offset, void* data, uint length);

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
		poke(offset, &val, sizeof(val));
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
