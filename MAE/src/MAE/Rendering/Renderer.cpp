#include <MAE/Rendering/RendererImpl.h>

#include <MAE/Rendering/VertexBufferImpl.h>

void RendererImpl::release() {
	::delete this;
}

VertexBuffer* RendererImpl::createVertexBuffer(uint length) {
	return ::new VertexBufferImpl(length, device);
}
