#pragma once

#include <MAE/Rendering/VertexData.h>

#include <d3d9.h>
#include <vector>

class VertexDataImpl: public VertexData {
public:
	VertexDataImpl(LPDIRECT3DDEVICE9 device, class VertexDataBuilderImpl* vdb);
	~VertexDataImpl();

	void replaceVertexBuffer(class VertexBuffer* old, class VertexBuffer* replacement);
	void setIndexBuffer(class IndexBuffer* ib);

	void set(LPDIRECT3DDEVICE9 device);

	inline uint getNumVertices() {
		return numVertices;
	}

private:
	struct StreamInfo {
		LPDIRECT3DVERTEXBUFFER9 vb;
		uint offset;
		uint stride;
	};

	uint numVertices;

	LPDIRECT3DINDEXBUFFER9 ib;
	LPDIRECT3DVERTEXDECLARATION9 decl;
	StreamInfo* streamInfoArray;
};
