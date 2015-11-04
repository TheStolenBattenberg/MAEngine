#include "MABullet.h"

DLLEXPORT MABullet_Free()
{
	//TODO: free stuff
	return 1;
}

DLLEXPORT MAB_Vec(double n)
{
	switch ((int)n)
	{
	case 0:
		return G.ReturnVec.x();
	case 1:
		return G.ReturnVec.y();
	case 2:
		return G.ReturnVec.z();
	}
	return 0;
}

DLLEXPORT MAB_Quat(double n)
{
	switch ((int)n)
	{
	case 0:
		return G.ReturnQuat.x();
	case 1:
		return G.ReturnQuat.y();
	case 2:
		return G.ReturnQuat.z();
	case 3:
		return G.ReturnQuat.w();
	}
	return 0;
}
