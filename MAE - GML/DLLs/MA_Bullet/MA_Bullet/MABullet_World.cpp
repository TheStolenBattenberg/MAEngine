#include "MABullet.h"

DLLEXPORT MAB_WorldCreate()
{
	if (G.worldExists()) return 0; //don't create world if it already exists

	G.CollisionConfiguration = new btDefaultCollisionConfiguration();
	G.Dispatcher = new btCollisionDispatcher(G.CollisionConfiguration);
	G.Broadphase = new btDbvtBroadphase;
	//G.Broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	G.Solver = new btSequentialImpulseConstraintSolver();
	G.World = new btDiscreteDynamicsWorld(G.Dispatcher, G.Broadphase, G.Solver, G.CollisionConfiguration);
	G.World->setGravity(btVector3(0, 0, -10));//default gravity

	return 1;
}

DLLEXPORT MAB_WorldDestroy()
{
	if (!G.worldExists()) return 0;
	for (int i = G.World->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = G.World->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		G.World->removeCollisionObject(obj);
		delete obj;
	}
	G.Bodies.clear();
	delete G.World;
	delete G.Solver;
	delete G.Dispatcher;
	delete G.CollisionConfiguration;
	delete G.Broadphase;
	G.World = nullptr;
	return 1;
}

DLLEXPORT MAB_WorldStep(double TimeStep, double MaxSubSteps, double FixedTimeStep)
{
	if (!G.worldExists()) return 0;
	G.World->stepSimulation((btScalar)TimeStep, (int)MaxSubSteps, (btScalar)FixedTimeStep);
	return 1;
}

DLLEXPORT MAB_WorldSetGravity(double X, double Y, double Z)
{
	if (!G.worldExists()) return 0;
	G.World->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT MAB_WorldGetBodyCount()
{
	if (!G.worldExists()) return 0;
	return G.World->getNumCollisionObjects();
}