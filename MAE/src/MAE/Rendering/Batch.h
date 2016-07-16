#pragma once

#include <MAE/Core/Types.h>
#include <MAE/Rendering/Renderer.h>
#include <MAE/Rendering/VertexBuffer.h>
#include <MAE/Rendering/VertexData.h>

enum BatchFlags {
	BatchFlagNoDoubleBuffer = 0x01,
	BatchFlagIgnoreSize     = 0x02 // TODO: Implement
};

template<uint flags = 0> class Batch {
public:
	typedef void RenderFunc(Renderer*, VertexBuffer*, VertexData*);
	typedef VertexData* BuildDataFunc(Renderer*, VertexBuffer*);

	Batch(Renderer* renderer, BuildDataFunc buildDataFunc, uint size):
		renderer(renderer), size(size), buildDataFunc(buildDataFunc) {

		vd = buildDataFunc(vb = renderer->createVertexBuffer(size));

		if (flags & BatchFlagNoDoubleBuffer == 0)
			vdBack = buildDataFunc(vbBack = renderer->createVertexBuffer(size));
	}

	~Batch() {
		delete vb;

		if (flags & BatchFlagNoDoubleBuffer == 0)
			delete vbBack;
	}

	template<typename T> void add(const T& data) {
		add(&data, sizeof(data));
	}

	template<typename T> void setSize(uint count) {
		setSize(count * sizeof(T));
	}

	void add(const void* data, uint length) {
		if (map + length > mapEnd) {
			if (length > size)
				setSize(length);
			else
				flush();

			begin();
		}
		
		memcpy(map, data, length);
		map += length;
	}

	void begin() {
		map = vb->map<ubyte>(0, 0, VertexBuffer::MapWrite);
		mapEnd = map + size;
	}

	void end() {
		// Buffer size is too small
		if (flushes > 0)
			setSize(size * (flushes + 1))
		else {
			flush();
			flushes = 0;
		}
	}

	void setSize(uint size) {
		flushes = 0;
		
		vb->unmap();
		renderFunc();

		this->size = size;

		vd = buildDataFunc(vb = renderer->createVertexBuffer(size));

		if (flags & BatchFlagNoDoubleBuffer == 0)
			vdBack = buildDataFunc(vbBack = renderer->createVertexBuffer(size));
	}

	inline uint getSize() {
		return size;
	}

	RenderFunc renderFunc;
	BuildDataFunc buildDataFunc;

private:
	void flush() {
		++flushes;

		vb->unmap();
		renderFunc();

		if (flags & BatchFlagNoDoubleBuffer == 0) {
			auto tmpVB = vb;
			vb = vbBack;
			vbBack = tmpVB;

			auto tmpVD = vd;
			vd = vdBack;
			vdBack = tmpVD;
		}

		map = vbBack->map<ubyte>(0, 0, VertexBuffer::MapRead);
		mapEnd = map + size;
	}

	uint size;
	uint flushes = 0;

	ubyte* map;
	ubyte* mapEnd;

	Renderer* renderer;

	VertexBuffer* vb;
	VertexBuffer* vbBack;

	VertexData* vd;
	VertexData* vdBack;
};
