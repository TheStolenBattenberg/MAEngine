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

	VertexDataImpl(LPDIRECT3DDEVICE9 device): device(device) { }
	~VertexDataImpl();

	void release();

	void setVertexBuffer(class VertexBuffer* vb, uint offset, uint stride);
	void addElement(uint index, uint type, uint offset);
	void build();
	void set();

private:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DVERTEXDECLARATION9 decl;
	StreamInfo* streamInfoArray;
	class VertexDataBuilder* builder;
};

class VertexDataBuilder {
public:
	void setVertexBuffer(LPDIRECT3DVERTEXBUFFER9 vb, uint offset, uint stride);
	void addElement(D3DDECLUSAGE usage, uint usageIndex, D3DDECLTYPE type, uint offset);
	LPDIRECT3DVERTEXDECLARATION9 buildDecl(LPDIRECT3DDEVICE9 device);
	VertexDataImpl::StreamInfo* buildStreamInfoArray();

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

	std::vector<BufferEntry> entries;
	BufferEntry* curEntry;
};
