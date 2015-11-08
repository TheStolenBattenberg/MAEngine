#include "MABullet.h"
#include "MABullet_DebugDraw.h"

DLLEXPORT MAB_Free()
{
	return G.destroyWorld();
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

DLLEXPORT MAB_HitResult(double n)
{
	switch ((int)n)
	{
	case 0:
		G.ReturnVec = G.HitResult.Position;
		return 1;
	case 1:
		G.ReturnVec = G.HitResult.Normal;
		return 1;
	case 2:
		return G.HitResult.Fraction;
	case 3:
		return G.HitResult.BodyID;
	case 4:
		return G.HitResult.UserIndex;
	}
	return 0;
}

DLLEXPORT MAB_OverlapResult(double n)
{
	return G.OverlapResults[(int)n];
}
