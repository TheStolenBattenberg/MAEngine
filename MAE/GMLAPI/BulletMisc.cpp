#include <MAE/Bullet/Bullet.h>
#include <MAE/Main.h>

#include <GMLAPI/Main.h>

DLLEXPORT double MAB_Vec(double n)
{
	TRYBEG();
	switch ((int)n)
	{
	case 0:
		return mabullet.returnVec.x();
	case 1:
		return mabullet.returnVec.y();
	case 2:
		return mabullet.returnVec.z();
	}
	return 0;
	TRYEND(0);
}

DLLEXPORT double MAB_Quat(double n)
{
	TRYBEG();
	switch ((int)n)
	{
	case 0:
		return mabullet.returnQuat.x();
	case 1:
		return mabullet.returnQuat.y();
	case 2:
		return mabullet.returnQuat.z();
	case 3:
		return mabullet.returnQuat.w();
	}
	return 0;
	TRYEND(0);
}

DLLEXPORT double MAB_HitResult(double n)
{
	TRYBEG();
	switch ((int)n)
	{
	case 0:
		mabullet.returnVec = mabullet.hitResult.position;
		return 1;
	case 1:
		mabullet.returnVec = mabullet.hitResult.normal;
		return 1;
	case 2:
		return mabullet.hitResult.fraction;
	case 3:
		return mabullet.hitResult.bodyID;
	case 4:
		return mabullet.hitResult.userIndex;
	}
	return 0;
	TRYEND(0);
}

DLLEXPORT double MAB_OverlapResult(double n)
{
	TRYBEG();
	return mabullet.overlapIDs[(int)n];
	TRYEND(0);
}
