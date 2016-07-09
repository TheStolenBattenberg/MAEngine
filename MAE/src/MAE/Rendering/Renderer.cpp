#include <MAE/Rendering/RendererImpl.h>

#include <MAE/Rendering/VertexBufferImpl.h>
#include <MAE/Rendering/VertexDataImpl.h>

void RendererImpl::release() {
	::delete this;
}

VertexBuffer* RendererImpl::createVertexBuffer(uint length) {
	return ::new VertexBufferImpl(length, device);
}

VertexData* RendererImpl::createVertexData() {
	return ::new VertexDataImpl();
}

void RendererImpl::buildVertexData(VertexData* vd) {
	((VertexDataImpl*) vd)->build(device);
}

void RendererImpl::setVertexData(VertexData* vd) {
	((VertexDataImpl*) vd)->set(device);
}
