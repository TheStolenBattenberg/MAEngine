#include "Bullet.h"
#include "Main.h"

DLLEXPORT double MAB_BodyCreate(double ShapeID, double Mass, double XRot, double YRot, double ZRot, double X, double Y, double Z)
{
	if (!mabullet->worldExists()) return -1;
	if (!mabullet->shapeExists(ShapeID)) return -2;

	btCollisionShape* shape = mabullet->getShape(ShapeID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)XRot, (btScalar)YRot, (btScalar)ZRot);
	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(quat, btVector3((btScalar)X, (btScalar)Y, (btScalar)Z)));
	btVector3 intertia(0.f, 0.f, 0.f);
	if (!dynamic_cast<btTriangleMeshShape*>(shape)) shape->calculateLocalInertia((btScalar)Mass, intertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI((btScalar)Mass, motionstate, shape, intertia);
	btRigidBody* rigidbody = new btRigidBody(bodyCI);
	MABody* body = new MABody(rigidbody);
	mabullet->World->addRigidBody(rigidbody);
	rigidbody->setUserIndex(mabullet->BodyCount);
	mabullet->Bodies[mabullet->BodyCount] = body;
	mabullet->BodyCount++;
	return mabullet->BodyCount - 1;
}

DLLEXPORT double MAB_BodyDestroy(double BodyID)
{
	if (!mabullet->bodyExists(BodyID)) return 0;
	btRigidBody* body = mabullet->getBody(BodyID);
	mabullet->World->removeCollisionObject(body);
	for (int i = body->getNumConstraintRefs() - 1; i >= 0; i--)
	{
		btTypedConstraint* constraint = body->getConstraintRef(i);
		mabullet->Constraints.erase(constraint->getUserConstraintId());
		delete constraint;
	}
	delete body->getMotionState();
	delete body;
	delete mabullet->Bodies[(int)BodyID];
	mabullet->Bodies.erase((int)BodyID);
	return 1;
}

DLLEXPORT double MAB_BodyGetPosition(double BodyID)
{
	btTransform trans;
	if(mabullet->UseMotionState) mabullet->getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet->getBody(BodyID)->getWorldTransform();
	mabullet->ReturnVec = trans.getOrigin();
	return 1;
}

DLLEXPORT double MAB_BodyGetRotationQuat(double BodyID)
{
	btTransform trans;
	if (mabullet->UseMotionState) mabullet->getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet->getBody(BodyID)->getWorldTransform();
	mabullet->ReturnQuat = trans.getRotation().inverse();
	return 1;
}

DLLEXPORT double MAB_BodyGetRotationEuler(double BodyID)
{
	btTransform trans;
	if (mabullet->UseMotionState) mabullet->getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	else trans = mabullet->getBody(BodyID)->getWorldTransform();
	mabullet->ReturnVec = MABullet::toEuler(trans.getBasis());
	return 1;
}

DLLEXPORT double MAB_BodyGetLinearVelocity      (double BodyID){ mabullet->ReturnVec = mabullet->getBody(BodyID)->getLinearVelocity();      return 1; }
DLLEXPORT double MAB_BodyGetAngularVelocity     (double BodyID){ mabullet->ReturnVec = mabullet->getBody(BodyID)->getAngularVelocity();     return 1; }
DLLEXPORT double MAB_BodyGetAnisotropicFriction (double BodyID){ mabullet->ReturnVec = mabullet->getBody(BodyID)->getAnisotropicFriction(); return 1; }
DLLEXPORT double MAB_BodyGetGravity             (double BodyID){ mabullet->ReturnVec = mabullet->getBody(BodyID)->getGravity();             return 1; }
DLLEXPORT double MAB_BodyGetAngularDamping      (double BodyID){ return mabullet->getBody(BodyID)->getAngularDamping(); }
DLLEXPORT double MAB_BodyGetLinearDamping       (double BodyID){ return mabullet->getBody(BodyID)->getLinearDamping(); }
DLLEXPORT double MAB_BodyGetFriction            (double BodyID){ return mabullet->getBody(BodyID)->getFriction(); }
DLLEXPORT double MAB_BodyGetRestitution         (double BodyID){ return mabullet->getBody(BodyID)->getRestitution(); }
DLLEXPORT double MAB_BodyGetRollingFriction     (double BodyID){ return mabullet->getBody(BodyID)->getRollingFriction(); }
DLLEXPORT double MAB_BodyGetDeactivationTime    (double BodyID){ return mabullet->getBody(BodyID)->getDeactivationTime(); }
DLLEXPORT double MAB_BodyIsStatic               (double BodyID){ return mabullet->getBody(BodyID)->isStaticObject(); }
DLLEXPORT double MAB_BodyIsKinematic            (double BodyID){ return mabullet->getBody(BodyID)->isKinematicObject(); }
DLLEXPORT double MAB_BodyGetShape               (double BodyID){ return mabullet->getBody(BodyID)->getCollisionShape()->getUserIndex(); }
DLLEXPORT double MAB_BodyIsActive               (double BodyID){ return mabullet->getBody(BodyID)->isActive(); }
DLLEXPORT double MAB_BodyGetGroup               (double BodyID){ return mabullet->getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup; }
DLLEXPORT double MAB_BodyGetMask                (double BodyID){ return mabullet->getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask; }
DLLEXPORT double MAB_BodyGetUserIndex           (double BodyID){ return mabullet->Bodies[(int)BodyID]->UserIndex; }

DLLEXPORT double MAB_BodyGetIgnore(double BodyID, double OtherBodyID)
{
	return mabullet->getBody(BodyID)->checkCollideWith(mabullet->getBody(OtherBodyID));
}

DLLEXPORT double MAB_BodySetPosition(double BodyID, double X, double Y, double Z)
{
	btTransform trans;
	btRigidBody* body = mabullet->getBody(BodyID);
	if (mabullet->UseMotionState) {
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
}

DLLEXPORT double MAB_BodySetRotationQuat(double BodyID, double X, double Y, double Z, double W)
{
	btTransform trans;
	btRigidBody* body = mabullet->getBody(BodyID);
	if (mabullet->UseMotionState) {
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
}

DLLEXPORT double MAB_BodySetRotationEuler(double BodyID, double X, double Y, double Z)
{
	btTransform trans;
	btRigidBody* body = mabullet->getBody(BodyID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)Z, (btScalar)Y, (btScalar)Z);
	if (mabullet->UseMotionState) {
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
}

DLLEXPORT double MAB_BodySetLinearVelocity(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setLinearVelocity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetAngularVelocity(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setAngularVelocity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetLinearFactor(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setLinearFactor(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetAngularFactor(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setAngularFactor(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetDamping(double BodyID, double linear, double angular){
	mabullet->getBody(BodyID)->setDamping((btScalar)linear, (btScalar)angular);
	return 1;}
DLLEXPORT double MAB_BodySetFriction(double BodyID, double friction){
	mabullet->getBody(BodyID)->setFriction((btScalar)friction);
	return 1;}
DLLEXPORT double MAB_BodySetAnisotropicFriction(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setAnisotropicFriction(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetRestitution(double BodyID, double restitution){
	mabullet->getBody(BodyID)->setRestitution((btScalar)restitution);
	return 1;}
DLLEXPORT double MAB_BodySetRollingFriction(double BodyID, double friction){
	mabullet->getBody(BodyID)->setRollingFriction((btScalar)friction);
	return 1;}
DLLEXPORT double MAB_BodySetGravity(double BodyID, double X, double Y, double Z){
	mabullet->getBody(BodyID)->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT double MAB_BodySetUserIndex(double BodyID, double index) {
	mabullet->Bodies[(int)BodyID]->UserIndex = (int)index;
	return 1;}
DLLEXPORT double MAB_BodySetDeactivationTime(double BodyID, double time) {
	mabullet->getBody(BodyID)->setDeactivationTime((btScalar)time);
	return 1;}
DLLEXPORT double MAB_BodyDisableDeactivation(double BodyID) {
	mabullet->getBody(BodyID)->forceActivationState(DISABLE_DEACTIVATION);
	return 1;}
DLLEXPORT double MAB_BodyActivate(double BodyID) {
	mabullet->getBody(BodyID)->activate(true);
	return 1;}
DLLEXPORT double MAB_BodyDeactivate(double BodyID) {
	mabullet->getBody(BodyID)->forceActivationState(DISABLE_SIMULATION);
	return 1;}
DLLEXPORT double MAB_BodySetShape(double BodyID, double ShapeID) {
	mabullet->getBody(BodyID)->setCollisionShape(mabullet->getShape(ShapeID));
	return 1;}
DLLEXPORT double MAB_BodySetIgnore(double BodyID, double IgnoreBodyID, double Ignore) {
	mabullet->getBody(BodyID)->setIgnoreCollisionCheck(mabullet->getBody(IgnoreBodyID), (Ignore > 0));
	return 1;}
DLLEXPORT double MAB_BodySetGroupMask(double BodyID, double group, double mask) {
	mabullet->getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup = (short)group;
	mabullet->getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask  = (short)mask;
	return 1;
}

DLLEXPORT double MAB_BodyApplyCentralImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet->getBody(BodyID)->applyCentralImpulse(impulse);
	else {
		btMatrix3x3 rot = mabullet->getBody(BodyID)->getWorldTransform().getBasis();
		mabullet->getBody(BodyID)->applyCentralImpulse(rot*impulse);
	}
	return 1;
}

DLLEXPORT double MAB_BodyApplyCentralForce(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 force = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet->getBody(BodyID)->applyCentralForce(force);
	else {
		btMatrix3x3 rot = mabullet->getBody(BodyID)->getWorldTransform().getBasis();
		mabullet->getBody(BodyID)->applyCentralForce(rot*force);
	}
	return 1;
}

DLLEXPORT double MAB_BodyApplyImpulse(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	mabullet->getBody(BodyID)->applyImpulse(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT double MAB_BodyApplyForce(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	mabullet->getBody(BodyID)->applyForce(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT double MAB_BodyApplyTorque(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet->getBody(BodyID)->applyTorque(impulse);
	else {
		btMatrix3x3 rot = mabullet->getBody(BodyID)->getWorldTransform().getBasis();
		mabullet->getBody(BodyID)->applyTorque(rot*impulse);
	}
	return 1;
}

DLLEXPORT double MAB_BodyApplyTorqueImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) mabullet->getBody(BodyID)->applyTorqueImpulse(impulse);
	else {
		btMatrix3x3 rot = mabullet->getBody(BodyID)->getWorldTransform().getBasis();
		mabullet->getBody(BodyID)->applyTorqueImpulse(rot*impulse);
	}
	return 1;
}
