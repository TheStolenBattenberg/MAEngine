#include <MAE/Rendering/Resources/TextureImpl.h>

TextureImpl::~TextureImpl() {
	tex->Release();
}
