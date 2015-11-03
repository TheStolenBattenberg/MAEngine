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
	body->setUserIndex(G.BodyCount);
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
