#define DLLEXPORT extern "C" __declspec (dllexport)

#include "dllbackend.h"

MADLLBackend MARenderBackend;

DLLEXPORT double MADX9_Init(long pointer)
{
	MARenderBackend.d3ddev = (LPDIRECT3DDEVICE9) pointer;
	return 1;
}
