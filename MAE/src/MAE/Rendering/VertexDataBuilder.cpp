#include <MAE/Rendering/VertexDataBuilderImpl.h>

#include <MAE/Rendering/Buffer/IndexBufferImpl.h>
#include <MAE/Rendering/Buffer/VertexBufferImpl.h>

#include <algorithm>
#include <cassert>

VertexDataBuilderImpl::~VertexDataBuilderImpl() { }

void VertexDataBuilderImpl::setIndexBuffer(IndexBuffer* ib) {
	this->ib = ((IndexBufferImpl*) ib)->getIndexBuffer();
}

void VertexDataBuilderImpl::setVertexBuffer(VertexBuffer* vb, uint offset, uint stride) {
	auto buf = ((VertexBufferImpl*) vb)->getVertexBuffer();

	auto it = std::find_if(entries.begin(), entries.end(), [buf, offset, stride](Entry entry) {
		return entry.vb == buf && entry.offset == offset && entry.stride == stride;
	});

	if (it == entries.end()) {
		if (curEntry != nullptr && curEntry->elements.empty())
			*curEntry = { buf, offset, stride, ((VertexBufferImpl*) vb)->getSize() };
		else {
			entries.push_back({ buf, offset, stride, ((VertexBufferImpl*) vb)->getSize() });
			curEntry = &*(entries.end() - 1);
		}
	}
	else
		curEntry = &*it;
}

void VertexDataBuilderImpl::addElement(uint location, uint type, uint offset) {
	uint table[] = {
		D3DDECLTYPE_FLOAT1, D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3, D3DDECLTYPE_FLOAT4
	};

	assert(("Invalid type", type < sizeof(table)));
	assert(("No VertexBuffer is set", curEntry != nullptr));

	curEntry->elements.push_back({ location & 0xFFFF, location >> 16, table[type], offset });
}
