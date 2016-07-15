#include <MAE/Rendering/Resources/TextureImpl.h>

TextureImpl::~TextureImpl() {
	tex->Release();
}

void TextureImpl::release() {
	::delete this;
}
