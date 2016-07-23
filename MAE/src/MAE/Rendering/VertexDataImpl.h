#pragma once

#include <MAE/Rendering/VertexData.h>

#include <d3d9.h>
#include <vector>

class VertexDataImpl: public VertexData {
public:
	VertexDataImpl(LPDIRECT3DDEVICE9 device);
	VertexDataImpl(const VertexDataImpl& impl);
	~VertexDataImpl();

	uint addVertexBuffer(class VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements);
	void build();
	void clear();
	void removeVertexBuffer(uint id);
	void setIndexBuffer(class IndexBuffer* ib);
	void setVertexBuffer(uint id, uint flags, class VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements);

	void reset();
	void resetInd();
	void set();
	void setInd();

	inline uint getNumVertices() {
		return m_numVertices;
	}

private:
	struct VertexBufferEntry {
		uint m_id;
		LPDIRECT3DVERTEXBUFFER9 m_vb;
		uint m_stride;
		uint m_offset;
		uint m_size;
		uint m_numElements;
		Element* m_elements;
	};

	uint getId();
	void clearDecl();
	void calcNumVerts();

	uint m_numVertices = -1;

	LPDIRECT3DDEVICE9 m_device = nullptr;
	LPDIRECT3DINDEXBUFFER9 m_ib = nullptr;
	LPDIRECT3DVERTEXDECLARATION9 m_decl = nullptr;

	std::vector<VertexBufferEntry> m_entries;
};
