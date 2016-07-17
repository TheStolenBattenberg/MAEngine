#include <MAE/Bullet/Bullet.h>
#include <MAE/Bullet/BulletDebugDraw.h>
#include <MAE/Main.h>

#include <GMLAPI/Main.h>

DLLEXPORT double MAB_WorldCreate(double UseMotionState)
{
	TRYBEG();
	if (mabullet.worldExists()) return 0;

	mabullet.collisionConfiguration = new btDefaultCollisionConfiguration();
	mabullet.dispatcher = new btCollisionDispatcher(mabullet.collisionConfiguration);
	mabullet.broadphase = new btDbvtBroadphase;
	//mabullet.Broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	mabullet.solver = new btSequentialImpulseConstraintSolver();
	mabullet.world = new btDiscreteDynamicsWorld(mabullet.dispatcher, mabullet.broadphase, mabullet.solver, mabullet.collisionConfiguration);
	mabullet.useMotionState = (UseMotionState > 0.5);

	//set the default gravity
	mabullet.world->setGravity(btVector3(0.f, 0.f, -10.f));

	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_WorldDestroy()
{
	TRYBEG();
	return mabullet.destroyWorld();
	TRYEND(0);
}

DLLEXPORT double MAB_WorldExists()
{
	TRYBEG();
	return mabullet.worldExists();
	TRYEND(0);
}

DLLEXPORT double MAB_WorldStep(double TimeStep, double MaxSubSteps, double FixedTimeStep)
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	mabullet.world->stepSimulation((btScalar)TimeStep, (int)MaxSubSteps, (btScalar)FixedTimeStep);
	if (mabullet.debugDrawer) static_cast<MABulletDebugDraw*>(mabullet.debugDrawer)->update = true;
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_WorldSetGravity(double X, double Y, double Z)
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	mabullet.world->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_WorldGetGravity()
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	mabullet.returnVec = mabullet.world->getGravity();
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_WorldGetBodyCount()
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	return mabullet.world->getNumCollisionObjects();
	TRYEND(0);
}

DLLEXPORT double MAB_WorldGetConstraintCount()
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	return mabullet.world->getNumConstraints();
	TRYEND(0);
}

DLLEXPORT double MAB_WorldDebugDraw()
{
	TRYBEG();
	if (!mabullet.worldExists()) return 0;
	if (!mabullet.debugDrawer) {
		MABulletDebugDraw* DebugDrawer = new MABulletDebugDraw;
		mabullet.debugDrawer = DebugDrawer;
		mabullet.world->setDebugDrawer(DebugDrawer);
	}
	MABulletDebugDraw* DebugDrawer = static_cast<MABulletDebugDraw*>(mabullet.debugDrawer);
	DebugDrawer->debugDraw(renderer);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_WorldRaycast(double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	TRYBEG();
	if (!mabullet.worldExists()) return -1;
	btVector3 start = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 end = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btCollisionWorld::ClosestRayResultCallback callback(start, end);
	callback.m_collisionFilterGroup = (short)Group;
	callback.m_collisionFilterMask = (short)Mask;
	mabullet.world->rayTest(start, end, callback);
	if (callback.hasHit())
	{
		mabullet.hitResult.position = callback.m_hitPointWorld;
		mabullet.hitResult.normal = callback.m_hitNormalWorld;
		mabullet.hitResult.fraction = callback.m_closestHitFraction;
		mabullet.hitResult.bodyID = callback.m_collisionObject->getUserIndex();
		mabullet.hitResult.userIndex = mabullet.bodies[mabullet.hitResult.bodyID]->userIndex;
		return 1;
	}
	return 0;
	TRYEND(-1);
}
/*
DLLEXPORT double MAB_WorldRaycastSingle(double BodyID, double X, double Y, double Z, double XT, double YT, double ZT)
{
	if (!mabullet.worldExists()) return -1;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionObject* obj = static_cast<btCollisionObject*>(mabullet.getBody(BodyID));
	btCollisionWorld::ClosestRayResultCallback callback(startvec, endvec);
	mabullet.world->rayTestSingle(start, end, mabullet.getBody(BodyID), mabullet.getBody(BodyID)->getCollisionShape(), mabullet.getBody(BodyID)->getWorldTransform(), callback);
	if (callback.hasHit())
	{
		mabullet.hitResult.Position = callback.m_hitPointWorld;
		mabullet.hitResult.Normal = callback.m_hitNormalWorld;
		mabullet.hitResult.Fraction = callback.m_closestHitFraction;
		mabullet.hitResult.BodyID = callback.m_collisionObject->getUserIndex();
		mabullet.hitResult.UserIndex = mabullet.bodies[mabullet.hitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}
*/

DLLEXPORT double MAB_WorldSweep(double ShapeID, double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	TRYBEG();
	//TODO: Fix this function because it doesn't work for some reason
	if (!mabullet.worldExists()) return -1;
	if (!mabullet.shapeExists(ShapeID)) return -2;
	btConvexShape* convex = dynamic_cast<btConvexShape*>(mabullet.getShape(ShapeID));
	if (!convex) return -3;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionWorld::ClosestConvexResultCallback callback(startvec, endvec);
	mabullet.world->convexSweepTest(convex, start, end, callback);
	if (callback.hasHit())
	{
		mabullet.hitResult.position = callback.m_hitPointWorld;
		mabullet.hitResult.normal = callback.m_hitNormalWorld;
		mabullet.hitResult.fraction = callback.m_closestHitFraction;
		mabullet.hitResult.bodyID = callback.m_hitCollisionObject->getUserIndex();
		mabullet.hitResult.userIndex = mabullet.bodies[mabullet.hitResult.bodyID]->userIndex;
		return 1;
	}
	return 0;
	TRYEND(-1);
}

DLLEXPORT double MAB_WorldOverlap(double ShapeID, double X, double Y, double Z, double RX, double RY, double RZ, double RW, double Group, double Mask)
{
	TRYBEG();
	if (!mabullet.worldExists()) return -1;
	if (!mabullet.shapeExists(ShapeID)) return -2;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	btCollisionObject* obj = new btCollisionObject();
	obj->setCollisionShape(mabullet.getShape(ShapeID));
	obj->setWorldTransform(trans);
	mabullet.world->addCollisionObject(obj, (short)Group, (short)Mask);
	mabullet.world->updateAabbs();
	MAOverlapCallback callback(obj);
	mabullet.overlapIDs.clear();
	mabullet.world->contactTest(obj, callback);
	mabullet.world->removeCollisionObject(obj);
	delete obj;
	return mabullet.overlapIDs.size();
	TRYEND(-1);
}
