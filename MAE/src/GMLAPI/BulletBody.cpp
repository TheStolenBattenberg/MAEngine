#include <MAE/Bullet/Bullet.h>
#include <MAE/Main.h>

#include <GMLAPI/Main.h>

DLLEXPORT double MAB_BodyCreate(double shapeID, double mass, double xRot, double yRot, double zRot, double x, double y, double z)
{
	TRYBEG();
	if (!mabullet.worldExists()) return -1;
	if (!mabullet.shapeExists(shapeID)) return -2;

	btCollisionShape* shape = mabullet.getShape(shapeID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)xRot, (btScalar)yRot, (btScalar)zRot);
	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(quat, btVector3((btScalar)x, (btScalar)y, (btScalar)z)));
	btVector3 intertia(0.f, 0.f, 0.f);
	if (!dynamic_cast<btTriangleMeshShape*>(shape)) shape->calculateLocalInertia((btScalar)mass, intertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI((btScalar)mass, motionstate, shape, intertia);
	btRigidBody* rigidbody = new btRigidBody(bodyCI);
	RigidBody* body = new RigidBody(rigidbody);
	mabullet.world->addRigidBody(rigidbody);
	rigidbody->setUserIndex(mabullet.bodyCount);
	mabullet.bodies[mabullet.bodyCount] = body;
	mabullet.bodyCount++;
	return mabullet.bodyCount - 1;
	TRYEND(-1);
}

DLLEXPORT double MAB_BodyDestroy(double BodyID)
{
	TRYBEG();
	if (!mabullet.bodyExists(BodyID)) return 0;
	btRigidBody* body = mabullet.getBody(BodyID);
	mabullet.world->removeCollisionObject(body);
	for (int i = body->getNumConstraintRefs() - 1; i >= 0; i--)
	{
		btTypedConstraint* constraint = body->getConstraintRef(i);
		mabullet.constraints.erase(constraint->getUserConstraintId());
		delete constraint;
	}
	delete body->getMotionState();
	delete body;
	delete mabullet.bodies[(int)BodyID];
	mabullet.bodies.erase((int)BodyID);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyGetPosition(double BodyID)
{
	TRYBEG();
	btTransform trans;
	if(mabullet.useMotionState) mabullet.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet.getBody(BodyID)->getWorldTransform();
	mabullet.returnVec = trans.getOrigin();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyGetRotationQuat(double BodyID)
{
	TRYBEG();
	btTransform trans;
	if (mabullet.useMotionState) mabullet.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet.getBody(BodyID)->getWorldTransform();
	mabullet.returnQuat = trans.getRotation().inverse();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyGetRotationEuler(double BodyID)
{
	TRYBEG();
	btTransform trans;
	if (mabullet.useMotionState) mabullet.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet.getBody(BodyID)->getWorldTransform();
	mabullet.returnVec = MABullet::toEuler(trans.getBasis());
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyGetLinearVelocity      (double BodyID){ TRYBEG(); mabullet.returnVec = mabullet.getBody(BodyID)->getLinearVelocity();      return 1; TRYEND(0); }
DLLEXPORT double MAB_BodyGetAngularVelocity     (double BodyID){ TRYBEG(); mabullet.returnVec = mabullet.getBody(BodyID)->getAngularVelocity();     return 1; TRYEND(0); }
DLLEXPORT double MAB_BodyGetAnisotropicFriction (double BodyID){ TRYBEG(); mabullet.returnVec = mabullet.getBody(BodyID)->getAnisotropicFriction(); return 1; TRYEND(0); }
DLLEXPORT double MAB_BodyGetGravity             (double BodyID){ TRYBEG(); mabullet.returnVec = mabullet.getBody(BodyID)->getGravity();             return 1; TRYEND(0); }
DLLEXPORT double MAB_BodyGetAngularDamping      (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getAngularDamping(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetLinearDamping       (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getLinearDamping(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetFriction            (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getFriction(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetRestitution         (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getRestitution(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetRollingFriction     (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getRollingFriction(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetDeactivationTime    (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getDeactivationTime(); TRYEND(-1); }
DLLEXPORT double MAB_BodyIsStatic               (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->isStaticObject(); TRYEND(-1); }
DLLEXPORT double MAB_BodyIsKinematic            (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->isKinematicObject(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetShape               (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getCollisionShape()->getUserIndex(); TRYEND(-1); }
DLLEXPORT double MAB_BodyIsActive               (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->isActive(); TRYEND(-1); }
DLLEXPORT double MAB_BodyGetGroup               (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup; TRYEND(-1); }
DLLEXPORT double MAB_BodyGetMask                (double BodyID){ TRYBEG(); return mabullet.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask; TRYEND(-1); }
DLLEXPORT double MAB_BodyGetUserIndex           (double BodyID){ TRYBEG(); return mabullet.bodies[(int)BodyID]->userIndex; TRYEND(-1); }

DLLEXPORT double MAB_BodyGetIgnore(double BodyID, double OtherBodyID)
{
	TRYBEG();
	return mabullet.getBody(BodyID)->checkCollideWith(mabullet.getBody(OtherBodyID));
	TRYEND(-1);
}

DLLEXPORT double MAB_BodySetPosition(double BodyID, double X, double Y, double Z)
{
	TRYBEG();
	btTransform trans;
	btRigidBody* body = mabullet.getBody(BodyID);
	if (mabullet.useMotionState) {
		body->getMotionState()->getWorldTransform(trans);
		trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
		body->getMotionState()->setWorldTransform(trans);
	}
	else {
		trans = body->getWorldTransform();
		trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
		body->setWorldTransform(trans);
	}	
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetRotationQuat(double BodyID, double X, double Y, double Z, double W)
{
	TRYBEG();
	btTransform trans;
	btRigidBody* body = mabullet.getBody(BodyID);
	if (mabullet.useMotionState) {
		body->getMotionState()->getWorldTransform(trans);
		trans.setRotation(btQuaternion((btScalar)X, (btScalar)Y, (btScalar)Z, -(btScalar)W));
		body->getMotionState()->setWorldTransform(trans);
	}
	else {
		trans = body->getWorldTransform();
		trans.setRotation(btQuaternion((btScalar)X, (btScalar)Y, (btScalar)Z, -(btScalar)W));
		body->setWorldTransform(trans);
	}
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetRotationEuler(double BodyID, double X, double Y, double Z)
{
	TRYBEG();
	btTransform trans;
	btRigidBody* body = mabullet.getBody(BodyID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)Z, (btScalar)Y, (btScalar)Z);
	if (mabullet.useMotionState) {
		body->getMotionState()->getWorldTransform(trans);
		trans.setRotation(quat);
		body->getMotionState()->setWorldTransform(trans);
	}
	else {
		trans = body->getWorldTransform();
		trans.setRotation(quat);
		body->setWorldTransform(trans);
	}
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetLinearVelocity(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setLinearVelocity(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetAngularVelocity(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setAngularVelocity(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetLinearFactor(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setLinearFactor(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetAngularFactor(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setAngularFactor(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetDamping(double BodyID, double linear, double angular) {
	TRYBEG();
	mabullet.getBody(BodyID)->setDamping((btScalar) linear, (btScalar) angular);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetFriction(double BodyID, double friction) {
	TRYBEG();
	mabullet.getBody(BodyID)->setFriction((btScalar) friction);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetAnisotropicFriction(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setAnisotropicFriction(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetRestitution(double BodyID, double restitution) {
	TRYBEG();
	mabullet.getBody(BodyID)->setRestitution((btScalar) restitution);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetRollingFriction(double BodyID, double friction) {
	TRYBEG();
	mabullet.getBody(BodyID)->setRollingFriction((btScalar) friction);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetGravity(double BodyID, double X, double Y, double Z) {
	TRYBEG();
	mabullet.getBody(BodyID)->setGravity(btVector3((btScalar) X, (btScalar) Y, (btScalar) Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetUserIndex(double BodyID, double index) {
	TRYBEG();
	mabullet.bodies[(int) BodyID]->userIndex = (int) index;
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetDeactivationTime(double BodyID, double time) {
	TRYBEG();
	mabullet.getBody(BodyID)->setDeactivationTime((btScalar) time);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyDisableDeactivation(double BodyID) {
	TRYBEG();
	mabullet.getBody(BodyID)->forceActivationState(DISABLE_DEACTIVATION);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyActivate(double BodyID) {
	TRYBEG();
	mabullet.getBody(BodyID)->activate(true);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyDeactivate(double BodyID) {
	TRYBEG();
	mabullet.getBody(BodyID)->forceActivationState(DISABLE_SIMULATION);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetShape(double BodyID, double ShapeID) {
	TRYBEG();
	mabullet.getBody(BodyID)->setCollisionShape(mabullet.getShape(ShapeID));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetIgnore(double BodyID, double IgnoreBodyID, double Ignore) {
	TRYBEG();
	mabullet.getBody(BodyID)->setIgnoreCollisionCheck(mabullet.getBody(IgnoreBodyID), (Ignore > 0));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodySetGroupMask(double BodyID, double group, double mask) {
	TRYBEG();
	mabullet.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup = (short) group;
	mabullet.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask = (short) mask;
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyCentralImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	TRYBEG();
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet.getBody(BodyID)->applyCentralImpulse(impulse);
	else {
		btMatrix3x3 rot = mabullet.getBody(BodyID)->getWorldTransform().getBasis();
		mabullet.getBody(BodyID)->applyCentralImpulse(rot*impulse);
	}
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyCentralForce(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	TRYBEG();
	btVector3 force = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet.getBody(BodyID)->applyCentralForce(force);
	else {
		btMatrix3x3 rot = mabullet.getBody(BodyID)->getWorldTransform().getBasis();
		mabullet.getBody(BodyID)->applyCentralForce(rot*force);
	}
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyImpulse(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	TRYBEG();
	mabullet.getBody(BodyID)->applyImpulse(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyForce(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	TRYBEG();
	mabullet.getBody(BodyID)->applyForce(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyTorque(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	TRYBEG();
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet.getBody(BodyID)->applyTorque(impulse);
	else {
		btMatrix3x3 rot = mabullet.getBody(BodyID)->getWorldTransform().getBasis();
		mabullet.getBody(BodyID)->applyTorque(rot*impulse);
	}
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_BodyApplyTorqueImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	TRYBEG();
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet.getBody(BodyID)->applyTorqueImpulse(impulse);
	else {
		btMatrix3x3 rot = mabullet.getBody(BodyID)->getWorldTransform().getBasis();
		mabullet.getBody(BodyID)->applyTorqueImpulse(rot*impulse);
	}
	return 1;
	TRYEND(0);
}
