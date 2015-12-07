#include "MABullet.h"
#include "MABullet_DebugDraw.h"

DLLEXPORT MAB_WorldCreate(double UseMotionState)
{
	if (G.worldExists()) return 0;

	G.CollisionConfiguration = new btDefaultCollisionConfiguration();
	G.Dispatcher = new btCollisionDispatcher(G.CollisionConfiguration);
	G.Broadphase = new btDbvtBroadphase;
	//G.Broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	G.Solver = new btSequentialImpulseConstraintSolver();
	G.World = new btDiscreteDynamicsWorld(G.Dispatcher, G.Broadphase, G.Solver, G.CollisionConfiguration);
	G.UseMotionState = (UseMotionState > 0.5);

	//set the default gravity
	G.World->setGravity(btVector3(0.f, 0.f, -10.f));

	return 1;
}

DLLEXPORT MAB_WorldDestroy()
{
	return G.destroyWorld();
}

DLLEXPORT MAB_WorldExists()
{
	return (G.worldExists()) ? 1 : 0;
}

DLLEXPORT MAB_WorldStep(double TimeStep, double MaxSubSteps, double FixedTimeStep)
{
	if (!G.worldExists()) return 0;
	G.World->stepSimulation((btScalar)TimeStep, (int)MaxSubSteps, (btScalar)FixedTimeStep);
	if (G.DebugDrawer) static_cast<MABulletDebugDraw*>(G.DebugDrawer)->update = true;
	return 1;
}

DLLEXPORT MAB_WorldSetGravity(double X, double Y, double Z)
{
	if (!G.worldExists()) return 0;
	G.World->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT MAB_WorldGetGravity()
{
	if (!G.worldExists()) return 0;
	G.ReturnVec = G.World->getGravity();
	return 1;
}

DLLEXPORT MAB_WorldGetBodyCount()
{
	if (!G.worldExists()) return 0;
	return G.World->getNumCollisionObjects();
}

DLLEXPORT MAB_WorldGetConstraintCount()
{
	if (!G.worldExists()) return 0;
	return G.World->getNumConstraints();
}

DLLEXPORT MAB_WorldDebugDraw(LPDIRECT3DDEVICE9 pointer)
{
	if (!G.worldExists()) return 0;
	if (!G.DebugDrawer) {
		MABulletDebugDraw* DebugDrawer = new MABulletDebugDraw((LPDIRECT3DDEVICE9)pointer);
		G.DebugDrawer = DebugDrawer;
		G.World->setDebugDrawer(DebugDrawer);
	}
	MABulletDebugDraw* DebugDrawer = static_cast<MABulletDebugDraw*>(G.DebugDrawer);
	DebugDrawer->debugDraw();
	return 1;
}

DLLEXPORT MAB_WorldRaycast(double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	if (!G.worldExists()) return -1;
	btVector3 start = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 end = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btCollisionWorld::ClosestRayResultCallback callback(start, end);
	callback.m_collisionFilterGroup = (short)Group;
	callback.m_collisionFilterMask = (short)Mask;
	G.World->rayTest(start, end, callback);
	if (callback.hasHit())
	{
		G.HitResult.Position = callback.m_hitPointWorld;
		G.HitResult.Normal = callback.m_hitNormalWorld;
		G.HitResult.Fraction = callback.m_closestHitFraction;
		G.HitResult.BodyID = callback.m_collisionObject->getUserIndex();
		G.HitResult.UserIndex = G.Bodies[G.HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}
/*
DLLEXPORT MAB_WorldRaycastSingle(double BodyID, double X, double Y, double Z, double XT, double YT, double ZT)
{
	if (!G.worldExists()) return -1;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionObject* obj = static_cast<btCollisionObject*>(G.getBody(BodyID));
	btCollisionWorld::ClosestRayResultCallback callback(startvec, endvec);
	G.World->rayTestSingle(start, end, G.getBody(BodyID), G.getBody(BodyID)->getCollisionShape(), G.getBody(BodyID)->getWorldTransform(), callback);
	if (callback.hasHit())
	{
		G.HitResult.Position = callback.m_hitPointWorld;
		G.HitResult.Normal = callback.m_hitNormalWorld;
		G.HitResult.Fraction = callback.m_closestHitFraction;
		G.HitResult.BodyID = callback.m_collisionObject->getUserIndex();
		G.HitResult.UserIndex = G.Bodies[G.HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}
*/

DLLEXPORT MAB_WorldSweep(double ShapeID, double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	if (!G.worldExists()) return -1;
	if (!G.shapeExists(ShapeID)) return -2;
	btConvexShape* convex = dynamic_cast<btConvexShape*>(G.getShape(ShapeID));
	if (!convex) return -3;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionWorld::ClosestConvexResultCallback callback(startvec, endvec);
	G.World->convexSweepTest(convex, start, end, callback);
	if (callback.hasHit())
	{
		G.HitResult.Position = callback.m_hitPointWorld;
		G.HitResult.Normal = callback.m_hitNormalWorld;
		G.HitResult.Fraction = callback.m_closestHitFraction;
		G.HitResult.BodyID = callback.m_hitCollisionObject->getUserIndex();
		G.HitResult.UserIndex = G.Bodies[G.HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}

DLLEXPORT MAB_WorldOverlap(double ShapeID, double X, double Y, double Z, double RX, double RY, double RZ, double RW, double Group, double Mask)
{
	if (!G.worldExists()) return -1;
	if (!G.shapeExists(ShapeID)) return -2;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	btCollisionObject* obj = new btCollisionObject();
	obj->setCollisionShape(G.getShape(ShapeID));
	obj->setWorldTransform(trans);
	G.World->addCollisionObject(obj, (short)Group, (short)Mask);
	G.World->updateAabbs();
	MAOverlapCallback callback(obj);
	G.OverlapResults.clear();
	G.World->contactTest(obj, callback);
	G.World->removeCollisionObject(obj);
	delete obj;
	return G.OverlapResults.size();
}
