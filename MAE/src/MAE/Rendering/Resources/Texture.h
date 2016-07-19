#pragma once

#include <MAE/Core/Types.h>
#include <MAE/Core/Deletable.h>

#include <string>

class Texture: public Deletable {
public:
	virtual ~Texture() { };
};
