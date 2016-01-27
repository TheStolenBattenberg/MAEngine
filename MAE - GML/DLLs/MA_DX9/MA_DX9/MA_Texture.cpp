#include "Main.h"
#include "Types.h"
#include "Utils.h"
#include "Texture.h"

#include "MA_Main.h"

DLLEXPORT double MAE_TextureCreate()
{
	Texture* tex;
	
	ErrorCode ret = mamain->createTexture(tex);

	if (ret != ErrorOk)
		return ret;

	return VectorPushBackPointer(tex, textures);
}

DLLEXPORT double MADX9_TextureCreateFromFile(double index, const char* file, Texture::MipMaps mipmaps)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return tex->loadFromFile(file, mipmaps);
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double index, double ptr)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0 || DoubleToPtr(ptr) == 0)
		return mamain->setError(ErrorInv);

	return tex->createFromPointer((LPDIRECT3DTEXTURE9) DoubleToPtr(ptr));
}

DLLEXPORT double MADX9_TextureDestroy(double index)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	tex->release();
	textures[(uint) index] = 0;

	return 1;
}

DLLEXPORT double MADX9_TextureSet(double stage, double index)
{
	if (index < 0)
		return mamain->resetTexture((uint) stage);

	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return mamain->setTexture((uint) stage, tex);
}

DLLEXPORT double MADX9_TextureCreateFromFileInMemory(double index, const void* data, double length, Texture::MipMaps mipmaps)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return tex->loadFromFileInMemory(data, (uint) length, mipmaps);
}

DLLEXPORT double MADX9_TextureCreateEmpty(double index, double width, double height, double levels, double usage, double format, double pool)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return tex->create((uint) width, (uint) height, (uint) levels, (uint) usage, (D3DFORMAT) (uint) format, (D3DPOOL) (uint) pool);
}

DLLEXPORT double MADX9_TextureGenerateMipMaps(double index)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return tex->generateMipMaps();
}

DLLEXPORT double MADX9_TextureGetPointer(double index)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return PtrToDouble(0);

	LPDIRECT3DTEXTURE9 t;

	return tex->getTexture(t) != ErrorOk ? PtrToDouble(0) : PtrToDouble(t);
}

DLLEXPORT double MADX9_TextureGetSurfaceCount(double index)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	uint count;

	ErrorCode ret = tex->getSurfaceCount(count);

	return ret != ErrorOk ? ret : count;
}

DLLEXPORT double MADX9_TextureSetMipMapFilter(double index, double filter)
{
	Texture* tex = VectorGetPointerSafe((uint) index, textures);

	if (tex == 0)
		return mamain->setError(ErrorInv);

	return tex->setMipMapFilter((D3DTEXTUREFILTERTYPE) (uint) filter);
}

DLLEXPORT double MADX9_TextureUpdate(double destIndex, double srcIndex)
{
	Texture* dest = VectorGetPointerSafe((uint) destIndex, textures);
	Texture* src = VectorGetPointerSafe((uint) srcIndex, textures);

	if (dest == 0 || src == 0)
		return mamain->setError(ErrorInv);

	return dest->update(src);
}
