#include <MAE/Rendering/VertexDataImpl.h>

#include <MAE/Rendering/Buffer/IndexBufferImpl.h>
#include <MAE/Rendering/Buffer/VertexBufferImpl.h>

#include <algorithm>
#include <cassert>

VertexDataImpl::VertexDataImpl(LPDIRECT3DDEVICE9 device): m_device(device) { }

VertexDataImpl::VertexDataImpl(const VertexDataImpl& impl) {
	*this = impl;

	// Copy arrays so they don't get deleted when the other class does
	for (auto& entry : m_entries) {
		if (entry.m_numElements == 0)
			continue;

		entry.m_elements = std::copy_n(entry.m_elements, entry.m_numElements, new Element[entry.m_numElements]);
	}

	// Add reference so declaration doesn't get lost
	if (m_decl != nullptr)
		m_decl->AddRef();
}

VertexDataImpl::~VertexDataImpl() {
	for (auto& entry : m_entries)
		delete entry.m_elements;

	if (m_decl != nullptr)
		m_decl->Release();
}

uint VertexDataImpl::addVertexBuffer(VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements) {
	assert(("VertexBuffer must exist", vb != nullptr));
	assert(("There has to be atleast one element", numElements != 0));

	clearDecl();

	auto vbPtr = ((VertexBufferImpl*) vb)->getVertexBuffer();

	auto it = std::find_if(m_entries.begin(), m_entries.end(), [vbPtr, stride, offset](auto entry) {
		return entry.m_vb == vbPtr && entry.m_stride == stride && entry.m_offset == offset;
	});

	// If vb, stride and offset match an entry, copy the elements
	if (it != m_entries.end()) {
		auto old = it->m_elements;
		auto oldSize = it->m_numElements;

		it->m_numElements += numElements;

		it->m_elements = std::copy_n(old, oldSize, new Element[it->m_numElements]);
		std::copy_n(elements, numElements, it->m_elements + oldSize);

		delete[] old;

		return it->m_id;
	}

	auto size = ((VertexBufferImpl*) vb)->getSize();
	auto id = getId();

	m_numVertices = std::min(m_numVertices, (size - offset) / stride);

	m_entries.push_back({
		id, vbPtr, stride, offset, size, numElements,
		std::copy_n(elements, numElements, new Element[numElements])
	});

	return id;
}

void VertexDataImpl::build() {
	if (m_decl != nullptr)
		return;

	auto size = 0;

	for (auto& entry : m_entries)
		size += entry.m_numElements;

	auto elements = new D3DVERTEXELEMENT9[size];
	auto curElem = elements;

	for (uint i = 0; i < m_entries.size(); ++i) {
		for (uint j = 0; j < m_entries[i].m_numElements; ++j) {
			const BYTE table[] = {
				D3DDECLTYPE_FLOAT1, D3DDECLTYPE_FLOAT2,
				D3DDECLTYPE_FLOAT3, D3DDECLTYPE_FLOAT4
			};

			auto& element = m_entries[i].m_elements[j];

			assert(("Invalid type", element.m_type >= sizeof(table)));

			*(curElem++) = {
				(WORD) i, (WORD) element.m_offset, table[element.m_type], D3DDECLMETHOD_DEFAULT,
				(BYTE) (element.m_location & 0xFFFF), (BYTE) (element.m_location >> 16)
			};
		}
	}

	if (FAILED(m_device->CreateVertexDeclaration(elements, &m_decl)))
		throw std::exception("Failed to create VertexDeclaration");

	delete[] elements;
}

void VertexDataImpl::clear() {
	for (auto& entry : m_entries)
		delete[] entry.m_elements;

	m_entries.clear();
	m_numVertices = -1;
	clearDecl();
}

void VertexDataImpl::removeVertexBuffer(uint id) {
	auto it = std::find_if(m_entries.begin(), m_entries.end(), [id](auto entry) { return entry.m_id == id; });

	if (it != m_entries.end()) {
		if (it->m_elements != nullptr)
			delete it->m_elements;

		m_entries.erase(it);
		clearDecl();

		if ((it->m_size - it->m_offset) / it->m_stride <= m_numVertices)
			calcNumVerts();
	}
}

void VertexDataImpl::setIndexBuffer(IndexBuffer* ib) {
	m_ib = ((IndexBufferImpl*) ib)->getIndexBuffer();
}

void VertexDataImpl::setVertexBuffer(uint id, uint flags, VertexBuffer* vb, uint stride, uint offset, uint numElements, const Element* elements) {
	if (flags == 0)
		return;

	auto it = std::find_if(m_entries.begin(), m_entries.end(), [id](auto entry) { return entry.m_id == id; });

	assert(("Couldn't find VertexBuffer entry", it != m_entries.end()));

	if (flags & SetVertexBuffer) {
		it->m_vb = ((VertexBufferImpl*) vb)->getVertexBuffer();
		it->m_size = ((VertexBufferImpl*) vb)->getSize();
	}

	if (flags & SetStride)
		it->m_stride = stride;

	if (flags & SetOffset)
		it->m_offset = offset;

	if (flags & SetElements) {
		delete[] it->m_elements;
		it->m_elements = std::copy_n(elements, numElements, new Element[numElements]);
		it->m_numElements = numElements;
		clearDecl();
	}

	if (flags & (SetVertexBuffer | SetStride | SetOffset))
		calcNumVerts();
}

void VertexDataImpl::reset() {
	for (uint i = 0; i < m_entries.size(); ++i)
		m_device->SetStreamSource(i, nullptr, 0, 0);
}

void VertexDataImpl::resetInd() {
	m_device->SetIndices(nullptr);
	reset();
}

void VertexDataImpl::set() {
	assert(("VertexData must be built before using it", m_decl != nullptr));

	m_device->SetVertexDeclaration(m_decl);

	for (uint i = 0; i < m_entries.size(); ++i)
		m_device->SetStreamSource(i, m_entries[i].m_vb, m_entries[i].m_offset, m_entries[i].m_stride);
}

void VertexDataImpl::setInd() {
	assert(("No index buffer was set", m_ib != nullptr));

	m_device->SetIndices(m_ib);
	set();
}

uint VertexDataImpl::getId() {
	uint maxId = 0;

	for (auto& entry : m_entries)
		maxId = std::max(maxId, entry.m_id);
	
	return maxId + 1;
}

void VertexDataImpl::clearDecl() {
	if (m_decl != nullptr) {
		m_decl->Release();
		m_decl = nullptr;
	}
}

void VertexDataImpl::calcNumVerts() {
	m_numVertices = -1;

	for (auto& entry : m_entries)
		m_numVertices = std::min(m_numVertices, (entry.m_size - entry.m_offset) / entry.m_stride);
}
