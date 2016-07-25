#include <MAE/Bullet/Bullet.h>

MABullet mabullet;

double MABullet::addShape(btCollisionShape* shape) {
	shapes[shapeCount] = shape;
	shape->setUserIndex(shapeCount);
	shapeCount++;
	return shapeCount - 1;
}

double MABullet::addConstraint(btTypedConstraint* constraint) {
	constraints[constraintCount] = constraint;
	constraint->setUserConstraintId(constraintCount);
	constraintCount++;
	return constraintCount - 1;
}

bool MABullet::destroyWorld() {
	if (!worldExists()) return false;
	for (auto i : constraints) {
		world->removeConstraint(i.second);
		delete i.second;
	}
	constraints.clear();
	for (auto i : bodies) {
		world->removeCollisionObject(i.second->body);
		delete i.second->body->getMotionState();
		delete i.second->body;
		delete i.second;
	}
	bodies.clear();
	delete world;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
	if (debugDrawer) {
		delete debugDrawer;
		debugDrawer = nullptr;
	}
	world = nullptr;
	return true;
}

btVector3 MABullet::toEuler(btMatrix3x3 &tm) {
	btScalar x, y, z = 0;

	if (tm.getRow(2).x() < 0.999) {
		if (tm.getRow(2).x() > -0.999) x = atan2(-tm.getRow(2).y(), tm.getRow(2).z());
		else x = -atan2(tm.getRow(0).y(), tm.getRow(1).y());
	}
	else x = atan2(tm.getRow(0).y(), tm.getRow(1).y());

	if (tm.getRow(2).x() < 0.999) {
		if (tm.getRow(2).x() > -0.999) y = asin(tm.getRow(2).x());
		else y = -SIMD_HALF_PI;
	}
	else y = SIMD_HALF_PI;

	if (tm.getRow(2).x() < +0.999 && tm.getRow(2).x() > -0.999) {
		z = atan2(-tm.getRow(1).x(), tm.getRow(0).x());
	}
	else z = 0.f;

	return btVector3(x, y, z) * SIMD_DEGS_PER_RAD;
}
