#pragma once

#include <MAE/Main.h>
#include <MAE/Rendering/Resources/Surface.h>
#include <MAE/Rendering/Resources/Texture.h>
#include <MAE/Rendering/Resources/Shader.h>

#include <vector>

extern Main* mamain;
extern std::vector<Surface*> surfaces;
extern std::vector<Texture*> textures;
extern std::vector<Shader*> shaders;
extern std::vector<float> matStack;
