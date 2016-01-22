#pragma once

#include "Main.h"
#include "Surface.h"
#include "Texture.h"
#include "Shader.h"

#include <vector>

extern Main* mamain;
extern std::vector<Surface*> surfaces;
extern std::vector<Texture*> textures;
extern std::vector<Shader*> shaders;
extern std::vector<float> matStack;
