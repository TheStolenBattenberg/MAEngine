#include "MABullet.h"

DLLEXPORT MAB_BodyCreate(double ShapeID, double Mass, double XRot, double YRot, double ZRot, double X, double Y, double Z)
{
	if (!G.worldExists()) return -1;
	if (!G.shapeExists(ShapeID)) return -2;

	btCollisionShape* shape = G.getShape(ShapeID);
	btQuaternion quat;
	quat.setEulerZYX((btScalar)XRot, (btScalar)YRot, (btScalar)ZRot);
	btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(quat, btVector3((btScalar)X, (btScalar)Y, (btScalar)Z)));
	btVector3 intertia(0.f, 0.f, 0.f);
	shape->calculateLocalInertia((btScalar)Mass, intertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI((btScalar)Mass, MotionState, shape, intertia);
	btRigidBody* body = new btRigidBody(bodyCI);
	G.World->addRigidBody(body);
	G.Bodies[G.BodyCount] = body;
	body->setUserIndex(G.BodyCount);
	G.BodyCount++;	
	return G.BodyCount - 1;
}

DLLEXPORT MAB_BodyDestroy(double BodyID)
{
	int ID = (int)BodyID;
	if (!G.bodyExists(BodyID)) return 0;
	delete G.Bodies[ID];
	G.Bodies.erase(ID);
	return 1;
}

DLLEXPORT MAB_BodyGetPosition(double BodyID)
{
	G.ReturnVec = G.getBody(BodyID)->getWorldTransform().getOrigin();
	return 1;
}

DLLEXPORT MAB_BodyGetRotation(double BodyID)
{
	G.ReturnQuat = G.getBody(BodyID)->getWorldTransform().getRotation();
	return 1;
}