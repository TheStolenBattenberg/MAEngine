#pragma once

#include <MAE/Rendering/VertexData.h>

#include <d3d9.h>
#include <vector>

class VertexDataImpl: public VertexData {
public:
	struct StreamInfo {
		LPDIRECT3DVERTEXBUFFER9 vb;
		uint offset;
		uint stride;
	};

	~VertexDataImpl();

	void release();

	void setVertexBuffer(class VertexBuffer* vb, uint offset, uint stride);
	void addElement(uint location, uint type, uint offset);
	void build(LPDIRECT3DDEVICE9 device);
	void set(LPDIRECT3DDEVICE9 device);

	inline uint getNumVertices() {
		return numVertices;
	}

private:
	uint numVertices = 0;

	LPDIRECT3DVERTEXDECLARATION9 decl;
	StreamInfo* streamInfoArray;
	class VertexDataBuilder* builder;
};

class VertexDataBuilder {
public:
	VertexDataBuilder();

	void setVertexBuffer(class VertexBufferImpl* vb, uint offset, uint stride);
	void addElement(D3DDECLUSAGE usage, uint usageIndex, D3DDECLTYPE type, uint offset);
	LPDIRECT3DVERTEXDECLARATION9 buildDecl(LPDIRECT3DDEVICE9 device);
	VertexDataImpl::StreamInfo* buildStreamInfoArray();

	inline uint getNumVertices() {
		if (numVertices == std::numeric_limits<uint>::max())
			return 0;

		return numVertices;
	}

private:
	struct Element {
		D3DDECLUSAGE usage;
		uint index;
		D3DDECLTYPE type;
		uint offset;
	};

	struct BufferEntry {
		LPDIRECT3DVERTEXBUFFER9 vb;
		uint offset;
		uint stride;

		std::vector<Element> elements;
	};

	uint numVertices;

	std::vector<BufferEntry> entries;
	BufferEntry* curEntry;
};
