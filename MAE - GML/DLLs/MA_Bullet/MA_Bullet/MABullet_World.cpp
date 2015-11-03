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
	//TODO: Destroy the objects in the world
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
