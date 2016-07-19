#pragma once

#include <MAE/Rendering/VertexDataBuilder.h>

#include <d3d9.h>
#include <vector>

class VertexDataBuilderImpl: public VertexDataBuilder {
public:
	struct Element {
		uint usage;
		uint index;
		uint type;
		uint offset;
	};

	struct Entry {
		LPDIRECT3DVERTEXBUFFER9 vb;
		uint offset;
		uint stride;
		uint size;

		std::vector<Element> elements;
	};

	~VertexDataBuilderImpl();

	void setIndexBuffer(class IndexBuffer* ib);
	void setVertexBuffer(class VertexBuffer* vb, uint offset, uint stride);
	void addElement(uint location, uint type, uint offset);
	
	inline const std::vector<Entry>& getEntries() {
		return entries;
	}

	inline LPDIRECT3DINDEXBUFFER9 getIndexBuffer() {
		return ib;
	}

private:
	LPDIRECT3DINDEXBUFFER9 ib = nullptr;
	std::vector<Entry> entries;
	Entry* curEntry;
};
