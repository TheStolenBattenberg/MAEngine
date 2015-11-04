#include "MABullet.h"

DLLEXPORT MAB_BodyCreate(double ShapeID, double Mass, double XRot, double YRot, double ZRot, double X, double Y, double Z)
{
	if (!G.worldExists()) return -1;
	if (!G.shapeExists(ShapeID)) return -2;

	btCollisionShape* shape = G.getShape(ShapeID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)XRot, (btScalar)YRot, (btScalar)ZRot);
	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(quat, btVector3((btScalar)X, (btScalar)Y, (btScalar)Z)));
	btVector3 intertia(0.f, 0.f, 0.f);
	shape->calculateLocalInertia((btScalar)Mass, intertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI((btScalar)Mass, motionstate, shape, intertia);
	btRigidBody* body = new btRigidBody(bodyCI);
	G.World->addRigidBody(body);
	G.Bodies[G.BodyCount] = body;
	G.BodyCount++;	
	return G.BodyCount - 1;
}

DLLEXPORT MAB_BodyDestroy(double BodyID)
{
	if (!G.bodyExists(BodyID)) return 0;
	int ID = (int)BodyID;
	G.World->removeCollisionObject(G.Bodies[ID]);
	delete G.Bodies[ID]->getMotionState();
	delete G.Bodies[ID];
	G.Bodies.erase(ID);
	return 1;
}

DLLEXPORT MAB_BodyGetPosition(double BodyID)
{
	btTransform trans;
	G.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	G.ReturnVec = trans.getOrigin();
	return 1;
}

DLLEXPORT MAB_BodyGetRotationQuat(double BodyID)
{
	btTransform trans;
	G.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	G.ReturnQuat = trans.getRotation();
	return 1;
}

DLLEXPORT MAB_BodyGetRotationEuler(double BodyID)
{
	btTransform trans;
	G.getBody(BodyID)->getMotionState()->getWorldTransform(trans);
	G.ReturnVec = G.toEuler(trans.getBasis());
	return 1;
}

DLLEXPORT MAB_BodyGetLinearVelocity      (double BodyID){ G.ReturnVec = G.getBody(BodyID)->getLinearVelocity();      return 1; }
DLLEXPORT MAB_BodyGetAngularVelocity     (double BodyID){ G.ReturnVec = G.getBody(BodyID)->getAngularVelocity();     return 1; }
DLLEXPORT MAB_BodyGetAnisotropicFriction (double BodyID){ G.ReturnVec = G.getBody(BodyID)->getAnisotropicFriction(); return 1; }
DLLEXPORT MAB_BodyGetGravity             (double BodyID){ G.ReturnVec = G.getBody(BodyID)->getGravity();             return 1; }
DLLEXPORT MAB_BodyGetAngularDamping      (double BodyID){ return G.getBody(BodyID)->getAngularDamping(); }
DLLEXPORT MAB_BodyGetLinearDamping       (double BodyID){ return G.getBody(BodyID)->getLinearDamping(); }
DLLEXPORT MAB_BodyGetFriction            (double BodyID){ return G.getBody(BodyID)->getFriction(); }
DLLEXPORT MAB_BodyGetRestitution         (double BodyID){ return G.getBody(BodyID)->getRestitution(); }
DLLEXPORT MAB_BodyGetRollingFriction     (double BodyID){ return G.getBody(BodyID)->getRollingFriction(); }
DLLEXPORT MAB_BodyGetUserIndex           (double BodyID){ return G.getBody(BodyID)->getUserIndex(); }
DLLEXPORT MAB_BodyGetDeactivationTime    (double BodyID){ return G.getBody(BodyID)->getDeactivationTime(); }
DLLEXPORT MAB_BodyIsStatic               (double BodyID){ return G.getBody(BodyID)->isStaticObject(); }
DLLEXPORT MAB_BodyIsKinematic            (double BodyID){ return G.getBody(BodyID)->isKinematicObject(); }
DLLEXPORT MAB_BodyGetShape               (double BodyID){ return G.getBody(BodyID)->getCollisionShape()->getUserIndex(); }
DLLEXPORT MAB_BodyIsActive               (double BodyID){ return G.getBody(BodyID)->isActive(); }
DLLEXPORT MAB_BodyGetGroup               (double BodyID){ return G.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup; }
DLLEXPORT MAB_BodyGetMask                (double BodyID){ return G.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask; }

DLLEXPORT MAB_BodySetPosition(double BodyID, double X, double Y, double Z)
{
	btTransform trans;
	btRigidBody* body = G.getBody(BodyID);
	body->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	body->getMotionState()->setWorldTransform(trans);
	return 1;
}

DLLEXPORT MAB_BodySetRotationQuat(double BodyID, double X, double Y, double Z, double W)
{
	btTransform trans;
	btRigidBody* body = G.getBody(BodyID);
	body->getMotionState()->getWorldTransform(trans);
	trans.setRotation(btQuaternion((btScalar)X, (btScalar)Y, (btScalar)Z, (btScalar)W));
	body->getMotionState()->setWorldTransform(trans);
	return 1;
}

DLLEXPORT MAB_BodySetRotationEuler(double BodyID, double X, double Y, double Z)
{
	btTransform trans;
	btRigidBody* body = G.getBody(BodyID);
	body->getMotionState()->getWorldTransform(trans);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)Z, (btScalar)Y, (btScalar)Z);
	trans.setRotation(quat);
	body->getMotionState()->setWorldTransform(trans);
	return 1;
}

DLLEXPORT MAB_BodySetLinearVelocity(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setLinearVelocity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetAngularVelocity(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setAngularVelocity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetLinearFactor(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setLinearFactor(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetAngularFactor(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setAngularFactor(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetDamping(double BodyID, double linear, double angular){
	G.getBody(BodyID)->setDamping((btScalar)linear, (btScalar)angular);
	return 1;}
DLLEXPORT MAB_BodySetFriction(double BodyID, double friction){
	G.getBody(BodyID)->setFriction((btScalar)friction);
	return 1;}
DLLEXPORT MAB_BodySetAnisotropicFriction(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setAnisotropicFriction(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetRestitution(double BodyID, double restitution){
	G.getBody(BodyID)->setRestitution((btScalar)restitution);
	return 1;}
DLLEXPORT MAB_BodySetRollingFriction(double BodyID, double friction){
	G.getBody(BodyID)->setRollingFriction((btScalar)friction);
	return 1;}
DLLEXPORT MAB_BodySetGravity(double BodyID, double X, double Y, double Z){
	G.getBody(BodyID)->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;}
DLLEXPORT MAB_BodySetUserIndex(double BodyID, double index) {
	G.getBody(BodyID)->setUserIndex((int)index);
	return 1;}
DLLEXPORT MAB_BodySetDeactivationTime(double BodyID, double time) {
	G.getBody(BodyID)->setDeactivationTime((btScalar)time);
	return 1;}
DLLEXPORT MAB_BodyDisableDeactivation(double BodyID) {
	G.getBody(BodyID)->forceActivationState(DISABLE_DEACTIVATION);
	return 1;}
DLLEXPORT MAB_BodyActivate(double BodyID) {
	G.getBody(BodyID)->activate(true);
	return 1;}
DLLEXPORT MAB_BodyDeactivate(double BodyID) {
	G.getBody(BodyID)->forceActivationState(DISABLE_SIMULATION);
	return 1;}
DLLEXPORT MAB_BodySetShape(double BodyID, double ShapeID) {
	G.getBody(BodyID)->setCollisionShape(G.getShape(ShapeID));
	return 1;}
DLLEXPORT MAB_BodySetGroupMask(double BodyID, double group, double mask) {
	G.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterGroup = (short)group;
	G.getBody(BodyID)->getBroadphaseProxy()->m_collisionFilterMask  = (short)mask;
	return 1;
}

DLLEXPORT MAB_BodyApplyCentralImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) G.getBody(BodyID)->applyCentralImpulse(impulse);
	else {
		btMatrix3x3 rot = G.getBody(BodyID)->getWorldTransform().getBasis();
		G.getBody(BodyID)->applyCentralImpulse(rot*impulse);
	}
	return 1;
}

DLLEXPORT MAB_BodyApplyCentralForce(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 force = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) G.getBody(BodyID)->applyCentralForce(force);
	else {
		btMatrix3x3 rot = G.getBody(BodyID)->getWorldTransform().getBasis();
		G.getBody(BodyID)->applyCentralForce(rot*force);
	}
	return 1;
}

DLLEXPORT MAB_BodyApplyImpulse(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	G.getBody(BodyID)->applyImpulse(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT MAB_BodyApplyForce(double BodyID, double X, double Y, double Z, double XVel, double YVel, double ZVel)
{
	G.getBody(BodyID)->applyForce(btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel), btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT MAB_BodyApplyTorque(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) G.getBody(BodyID)->applyTorque(impulse);
	else {
		btMatrix3x3 rot = G.getBody(BodyID)->getWorldTransform().getBasis();
		G.getBody(BodyID)->applyTorque(rot*impulse);
	}
	return 1;
}

DLLEXPORT MAB_BodyApplyTorqueImpulse(double BodyID, double XVel, double YVel, double ZVel, double relative)
{
	btVector3 impulse = btVector3((btScalar)XVel, (btScalar)YVel, (btScalar)ZVel);
	if (relative <= 0) G.getBody(BodyID)->applyTorqueImpulse(impulse);
	else {
		btMatrix3x3 rot = G.getBody(BodyID)->getWorldTransform().getBasis();
		G.getBody(BodyID)->applyTorqueImpulse(rot*impulse);
	}
	return 1;
}
