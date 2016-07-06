#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/Resources/TextureImpl.h>

TextureImpl::~TextureImpl() {
	main->removeTexture(this);

	if (tex != 0)
		tex->Release();
}

void TextureImpl::release() {
	::delete this;
}

void TextureImpl::loadFromFile(std::string file, MipMaps mipmaps) {
	if (tex != 0) {
		tex->Release();
		tex = 0;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(main->d3ddev, file.c_str(), 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw new std::exception("Failed to load texture");
}

void TextureImpl::loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps) {
	if (tex != 0) {
		tex->Release();
		tex = 0;
	}

	if (FAILED(D3DXCreateTextureFromFileInMemoryEx(main->d3ddev, data, length, 0, 0, mipmaps == MipMapsGenerate ? 0 : (mipmaps == MipMapsFromFile ? D3DX_FROM_FILE : 1), 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex)))
		throw new std::exception("Failed to load texture");
}
