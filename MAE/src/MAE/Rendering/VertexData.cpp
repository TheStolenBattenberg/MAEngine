#include <MAE/Rendering/VertexDataImpl.h>

#include <MAE/Rendering/VertexBufferImpl.h>

#include <algorithm>
#include <cassert>

VertexDataImpl::~VertexDataImpl() {
	decl->Release();
	delete streamInfoArray;

	if (builder != nullptr)
		delete builder;
}

void VertexDataImpl::release() {
	::delete this;
}

void VertexDataImpl::setVertexBuffer(VertexBuffer* vb, uint offset, uint stride) {
	if (builder == nullptr)
		builder = new VertexDataBuilder();

	builder->setVertexBuffer(((VertexBufferImpl*) vb)->getVertexBuffer(), offset, stride);
}

void VertexDataImpl::addElement(uint location, uint type, uint offset) {
	assert(("VertexData: setVertexBuffer must be called before adding any Element", builder != nullptr));
	assert(("Invalid type", type >= TypeMax));

	D3DDECLTYPE table[] = {
		D3DDECLTYPE_FLOAT1, D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3, D3DDECLTYPE_FLOAT4
	};

	builder->addElement((D3DDECLUSAGE) (location & 0xFFFF), location >> 16, table[type], offset);
}

void VertexDataImpl::build(LPDIRECT3DDEVICE9 device) {
	assert(("VertexDeclaration was already built", decl == nullptr));
	assert(("StreamInfo Array was already built", streamInfoArray == nullptr));

	decl = builder->buildDecl(device);
	streamInfoArray = builder->buildStreamInfoArray();

	delete builder;
	builder = nullptr;
}

void VertexDataImpl::set(LPDIRECT3DDEVICE9 device) {
	assert(("VertexDeclaration isn't built", decl != nullptr));
	assert(("StreamInfo Array isn't built", streamInfoArray != nullptr));

	device->SetVertexDeclaration(decl);

	for (auto i = 0; streamInfoArray[i].vb != nullptr; ++i)
		device->SetStreamSource(i, streamInfoArray[i].vb, streamInfoArray[i].offset, streamInfoArray[i].stride);
}

void VertexDataBuilder::setVertexBuffer(LPDIRECT3DVERTEXBUFFER9 vb, uint offset, uint stride) {
	auto it = std::find_if(entries.begin(), entries.end(), [vb, offset, stride](BufferEntry entry) {
		return entry.vb == vb && entry.offset == offset && entry.stride == stride;
	});

	if (it == entries.end()) {
		entries.push_back({ vb, offset, stride });
		it = entries.end() - 1;
	}

	curEntry = &*it;
}

void VertexDataBuilder::addElement(D3DDECLUSAGE usage, uint usageIndex, D3DDECLTYPE type, uint offset) {
	assert(("No VertexBuffer was set", curEntry != nullptr));

	curEntry->elements.push_back({ usage, usageIndex, type, offset });
}

LPDIRECT3DVERTEXDECLARATION9 VertexDataBuilder::buildDecl(LPDIRECT3DDEVICE9 device) {
	std::vector<D3DVERTEXELEMENT9> elements;

	for (uint i = 0; i < entries.size(); ++i)
		for (auto element : entries[i].elements)
			elements.push_back({
				(ushort) i, (ushort) element.offset,
				(ubyte) element.type, D3DDECLMETHOD_DEFAULT,
				(ubyte) element.usage, (ubyte) element.index
			});

	elements.push_back(D3DDECL_END());

	LPDIRECT3DVERTEXDECLARATION9 decl;

	if (FAILED(device->CreateVertexDeclaration(elements.data(), &decl)))
		throw new std::exception("Failed to create VertexDeclaration");

	return decl;
}

VertexDataImpl::StreamInfo* VertexDataBuilder::buildStreamInfoArray() {
	auto arr = new VertexDataImpl::StreamInfo[entries.size() + 1];

	for (uint i = 0; i < entries.size(); ++i)
		arr[i] = { entries[i].vb, entries[i].offset, entries[i].stride };
	
	arr[entries.size()] = { nullptr, 0, 0 };

	return arr;
}
