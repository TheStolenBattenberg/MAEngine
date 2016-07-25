#pragma once

#include <memory.h>
#include <cassert>

#include <MAE/Core/Types.h>

class Stream {
public:
	virtual ~Stream() { }

	template<typename T> T read() {
		T tmp;
		read(&tmp, sizeof(tmp));
		return tmp;
	}

	template<typename T> void write(const T& value) {
		write(&value, sizeof(T));
	}

	template<typename T> T peek(uint offset) {
		T tmp;
		peek(offset, &tmp, sizeof(tmp));
		return tmp;
	}

	template<typename T> void poke(uint offset, const T& value) {
		poke(offset, &value, sizeof(T));
	}

	virtual void read(void* dest, uint size) = 0;
	virtual void write(const void* src, uint size) = 0;
	virtual void peek(uint offset, void* dest, uint size) = 0;
	virtual void poke(uint offset, const void* src, uint size) = 0;
	virtual uint tell() = 0;
	virtual void seek(uint pos) = 0;
};

class MemoryStream: public Stream {
public:
	MemoryStream(void* data): data(data), pos(0) { }

	virtual ~MemoryStream() { }

	virtual void read(void* dest, uint size) {
		memcpy(dest, (ubyte*) data + pos, size);
		pos += size;
	}

	virtual void write(const void* src, uint size) {
		memcpy((ubyte*) data + pos, src, size);
		pos += size;
	}

	virtual void peek(uint offset, void* dest, uint size) {
		memcpy(dest, (ubyte*) data + offset, size);
	}

	virtual void poke(uint offset, const void* src, uint size) {
		memcpy((ubyte*) data + offset, src, size);
	}

	virtual uint tell() {
		return pos;
	}

	virtual void seek(uint pos) {
		this->pos = pos;
	}

private:
	void* data;
	uint pos;
};
