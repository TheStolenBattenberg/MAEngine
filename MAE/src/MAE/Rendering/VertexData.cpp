#include <MAE/Rendering/VertexDataImpl.h>

#include <MAE/Rendering/Buffer/IndexBufferImpl.h>
#include <MAE/Rendering/Buffer/VertexBufferImpl.h>
#include <MAE/Rendering/VertexDataBuilderImpl.h>

#include <algorithm>
#include <cassert>

VertexDataImpl::VertexDataImpl(LPDIRECT3DDEVICE9 device, VertexDataBuilderImpl* vdb) {
	assert(("VertexDataBuilder must not be empty", !vdb->getEntries().empty()));
	assert(("VertexDataBuilder must not be empty", !vdb->getEntries()[0].elements.empty()));

	auto& entries = vdb->getEntries();

	// Build VertexDeclaration

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
		throw std::exception("Failed to create VertexDeclaration");

	// Create StreamInfo array

	auto arr = new VertexDataImpl::StreamInfo[entries.size() + 1];

	for (uint i = 0; i < entries.size(); ++i)
		arr[i] = { entries[i].vb, entries[i].offset, entries[i].stride };

	arr[entries.size()] = { nullptr, 0, 0 };

	// Count how many vertices can be accessed

	numVertices = std::numeric_limits<uint>::max();

	for (auto& i : entries)
		numVertices = std::min(numVertices, (i.size - i.offset) / i.stride);

	ib = vdb->getIndexBuffer();
}

VertexDataImpl::~VertexDataImpl() {
	decl->Release();
	delete streamInfoArray;
}

void VertexDataImpl::release() {
	::delete this;
}

void VertexDataImpl::replaceVertexBuffer(VertexBuffer* old, VertexBuffer* replacement) {
	auto vb = ((VertexBufferImpl*) old)->getVertexBuffer();

	for (auto i = streamInfoArray; i->vb != nullptr; ++i)
		if (i->vb == vb)
			i->vb = ((VertexBufferImpl*) replacement)->getVertexBuffer();
}

void VertexDataImpl::setIndexBuffer(IndexBuffer* ib) {
	this->ib = ((IndexBufferImpl*) ib)->getIndexBuffer();
}

void VertexDataImpl::set(LPDIRECT3DDEVICE9 device) {
	device->SetVertexDeclaration(decl);

	if (ib != nullptr)
		device->SetIndices(ib);

	for (auto i = 0; streamInfoArray[i].vb != nullptr; ++i)
		device->SetStreamSource(i, streamInfoArray[i].vb, streamInfoArray[i].offset, streamInfoArray[i].stride);
}
