#pragma once

#include <MAE/Core/Error.h>
#include <MAE/Core/Releasable.h>

#include <string>

class Texture: public Releasable {
public:
	enum MipMaps {
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	virtual void loadFromFile(std::string file, MipMaps mipmaps) = 0;
	virtual void loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps) = 0;
};
