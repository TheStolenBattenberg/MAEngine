#pragma once

#include <MAE/Main.h>
#include <MAE/Core/UnorderedVector.h>

#include <GMLAPI/Stream.h>

#include <vector>

#define TRYBEG() try { do { } while (0)
#define TRYEND(ret) } catch (std::exception ex) { error(ex.what()); return (ret); } do { } while (0)

extern Main* mamain;
extern std::vector<float> matStack;
extern UnorderedVector<Stream*> streams;
extern class Renderer* renderer;

void error(const char* msg);
