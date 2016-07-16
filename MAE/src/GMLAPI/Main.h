#pragma once

#include <MAE/Main.h>
#include <MAE/Core/UnorderedVector.h>

#include <GMLAPI/Stream.h>

#include <vector>

extern Main* mamain;
extern std::vector<float> matStack;
extern UnorderedVector<Stream*> streams;
extern class Renderer* renderer;
