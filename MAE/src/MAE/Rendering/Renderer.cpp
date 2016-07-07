#include <MAE/Rendering/RendererImpl.h>

void RendererImpl::release() {
	::delete this;
}
