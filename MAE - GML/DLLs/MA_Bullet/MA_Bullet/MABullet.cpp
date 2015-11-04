#include "MABullet.h"

MABullet G;

btVector3 MABullet::toEuler(btMatrix3x3 &tm)
{
	btScalar x, y, z = 0;

	if (tm.getRow(2).x() < 0.999)
	{
		if (tm.getRow(2).x() > -0.999)
			x = atan2(-tm.getRow(2).y(), tm.getRow(2).z());
		else
			x = -atan2(tm.getRow(0).y(), tm.getRow(1).y());
	}
	else
		x = atan2(tm.getRow(0).y(), tm.getRow(1).y());

	if (tm.getRow(2).x() < 0.999)
	{
		if (tm.getRow(2).x() > -0.999)
			y = asin(tm.getRow(2).x());
		else
			y = -SIMD_HALF_PI;
	}
	else
		y = SIMD_HALF_PI;

	if (tm.getRow(2).x()< +0.999 && tm.getRow(2).x() > -0.999)
		z = atan2(-tm.getRow(1).x(), tm.getRow(0).x());
	else z = 0.f;

	return btVector3(x*SIMD_DEGS_PER_RAD, y*SIMD_DEGS_PER_RAD, z*SIMD_DEGS_PER_RAD);
}
