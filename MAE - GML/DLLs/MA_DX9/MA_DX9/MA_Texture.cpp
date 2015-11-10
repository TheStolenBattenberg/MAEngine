#include "Main.h"
#include "Types.h"

DLLEXPORT double MADX9_TextureCreateFromFile(const char* file, Texture::MipMaps mipmaps)
{
	Texture* tex = new Texture();

	if (!tex->loadFromFile(file, mipmaps))
	{
		delete tex;
		return -1;
	}

	for (uint i = 0; i < mamain.Textures.size(); ++i)
	{
		if (mamain.Textures[i] == 0)
		{
			mamain.Textures[i] = tex;
			return i;
		}
	}

	mamain.Textures.push_back(tex);
	return mamain.Textures.size() - 1;
}

DLLEXPORT double MADX9_TextureCreateFromPointer(double ptr)
{
	Texture* tex = new Texture();

	memcpy(&tex->tex, &ptr, sizeof(tex->tex));

	if (tex->tex == 0)
	{
		delete tex;
		return -1;
	}

	tex->tex->AddRef();

	for (uint i = 0; i < mamain.Textures.size(); ++i)
	{
		if (mamain.Textures[i] == 0)
		{
			mamain.Textures[i] = tex;
			return i;
		}
	}

	mamain.Textures.push_back(tex);
	return mamain.Textures.size() - 1;
}

DLLEXPORT double MADX9_TextureDestroy(double ind)
{
	if ((uint)ind >= mamain.Textures.size())
		return 0;

	if (mamain.Textures[(uint)ind] == 0)
		return 0;

	delete mamain.Textures[(uint)ind];
	mamain.Textures[(uint)ind] = 0;

	return 1;
}

DLLEXPORT double MADX9_TextureSet(double ind, double stage)
{
	if (ind < 0)
		return SUCCEEDED(mamain.d3ddev->SetTexture((uint)stage, 0));

	if ((uint)ind >= mamain.Textures.size())
		return 0;

	if (mamain.Textures[(uint)ind] == 0)
		return 0;

	return SUCCEEDED(mamain.d3ddev->SetTexture((uint)stage, mamain.Textures[(uint)ind]->tex));
}