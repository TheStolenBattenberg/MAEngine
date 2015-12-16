#include "Bullet.h"
#include "Main.h"

DLLEXPORT double MAB_Vec(double n)
{
	switch ((int)n)
	{
	case 0:
		return mabullet->ReturnVec.x();
	case 1:
		return mabullet->ReturnVec.y();
	case 2:
		return mabullet->ReturnVec.z();
	}
	return 0;
}

DLLEXPORT double MAB_Quat(double n)
{
	switch ((int)n)
	{
	case 0:
		return mabullet->ReturnQuat.x();
	case 1:
		return mabullet->ReturnQuat.y();
	case 2:
		return mabullet->ReturnQuat.z();
	case 3:
		return mabullet->ReturnQuat.w();
	}
	return 0;
}

DLLEXPORT double MAB_HitResult(double n)
{
	switch ((int)n)
	{
	case 0:
		mabullet->ReturnVec = mabullet->HitResult.Position;
		return 1;
	case 1:
		mabullet->ReturnVec = mabullet->HitResult.Normal;
		return 1;
	case 2:
		return mabullet->HitResult.Fraction;
	case 3:
		return mabullet->HitResult.BodyID;
	case 4:
		return mabullet->HitResult.UserIndex;
	}
	return 0;
}

DLLEXPORT double MAB_OverlapResult(double n)
{
	return mabullet->OverlapResults[(int)n];
}
