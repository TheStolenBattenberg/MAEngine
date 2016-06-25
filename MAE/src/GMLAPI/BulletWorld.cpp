#include <MAE/Bullet/Bullet.h>
#include <MAE/Bullet/BulletDebugDraw.h>
#include <MAE/Main.h>

DLLEXPORT double MAB_WorldCreate(double UseMotionState)
{
	if (mabullet->worldExists()) return 0;

	mabullet->CollisionConfiguration = new btDefaultCollisionConfiguration();
	mabullet->Dispatcher = new btCollisionDispatcher(mabullet->CollisionConfiguration);
	mabullet->Broadphase = new btDbvtBroadphase;
	//mabullet->Broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	mabullet->Solver = new btSequentialImpulseConstraintSolver();
	mabullet->World = new btDiscreteDynamicsWorld(mabullet->Dispatcher, mabullet->Broadphase, mabullet->Solver, mabullet->CollisionConfiguration);
	mabullet->UseMotionState = (UseMotionState > 0.5);

	//set the default gravity
	mabullet->World->setGravity(btVector3(0.f, 0.f, -10.f));

	return 1;
}

DLLEXPORT double MAB_WorldDestroy()
{
	return mabullet->destroyWorld();
}

DLLEXPORT double MAB_WorldExists()
{
	return mabullet->worldExists();
}

DLLEXPORT double MAB_WorldStep(double TimeStep, double MaxSubSteps, double FixedTimeStep)
{
	if (!mabullet->worldExists()) return 0;
	mabullet->World->stepSimulation((btScalar)TimeStep, (int)MaxSubSteps, (btScalar)FixedTimeStep);
	if (mabullet->DebugDrawer) static_cast<MABulletDebugDraw*>(mabullet->DebugDrawer)->update = true;
	return 1;
}

DLLEXPORT double MAB_WorldSetGravity(double X, double Y, double Z)
{
	if (!mabullet->worldExists()) return 0;
	mabullet->World->setGravity(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT double MAB_WorldGetGravity()
{
	if (!mabullet->worldExists()) return 0;
	mabullet->ReturnVec = mabullet->World->getGravity();
	return 1;
}

DLLEXPORT double MAB_WorldGetBodyCount()
{
	if (!mabullet->worldExists()) return 0;
	return mabullet->World->getNumCollisionObjects();
}

DLLEXPORT double MAB_WorldGetConstraintCount()
{
	if (!mabullet->worldExists()) return 0;
	return mabullet->World->getNumConstraints();
}

DLLEXPORT double MAB_WorldDebugDraw()
{
	if (!mabullet->worldExists()) return 0;
	if (!mabullet->DebugDrawer) {
		MABulletDebugDraw* DebugDrawer = new MABulletDebugDraw;
		mabullet->DebugDrawer = DebugDrawer;
		mabullet->World->setDebugDrawer(DebugDrawer);
	}
	MABulletDebugDraw* DebugDrawer = static_cast<MABulletDebugDraw*>(mabullet->DebugDrawer);
	DebugDrawer->debugDraw();
	return 1;
}

DLLEXPORT double MAB_WorldRaycast(double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	if (!mabullet->worldExists()) return -1;
	btVector3 start = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 end = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btCollisionWorld::ClosestRayResultCallback callback(start, end);
	callback.m_collisionFilterGroup = (short)Group;
	callback.m_collisionFilterMask = (short)Mask;
	mabullet->World->rayTest(start, end, callback);
	if (callback.hasHit())
	{
		mabullet->HitResult.Position = callback.m_hitPointWorld;
		mabullet->HitResult.Normal = callback.m_hitNormalWorld;
		mabullet->HitResult.Fraction = callback.m_closestHitFraction;
		mabullet->HitResult.BodyID = callback.m_collisionObject->getUserIndex();
		mabullet->HitResult.UserIndex = mabullet->Bodies[mabullet->HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}
/*
DLLEXPORT double MAB_WorldRaycastSingle(double BodyID, double X, double Y, double Z, double XT, double YT, double ZT)
{
	if (!mabullet->worldExists()) return -1;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionObject* obj = static_cast<btCollisionObject*>(mabullet->getBody(BodyID));
	btCollisionWorld::ClosestRayResultCallback callback(startvec, endvec);
	mabullet->World->rayTestSingle(start, end, mabullet->getBody(BodyID), mabullet->getBody(BodyID)->getCollisionShape(), mabullet->getBody(BodyID)->getWorldTransform(), callback);
	if (callback.hasHit())
	{
		mabullet->HitResult.Position = callback.m_hitPointWorld;
		mabullet->HitResult.Normal = callback.m_hitNormalWorld;
		mabullet->HitResult.Fraction = callback.m_closestHitFraction;
		mabullet->HitResult.BodyID = callback.m_collisionObject->getUserIndex();
		mabullet->HitResult.UserIndex = mabullet->Bodies[mabullet->HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}
*/

DLLEXPORT double MAB_WorldSweep(double ShapeID, double X, double Y, double Z, double XT, double YT, double ZT, double Group, double Mask)
{
	//TODO: Fix this because it doesn't work for some reason
	if (!mabullet->worldExists()) return -1;
	if (!mabullet->shapeExists(ShapeID)) return -2;
	btConvexShape* convex = dynamic_cast<btConvexShape*>(mabullet->getShape(ShapeID));
	if (!convex) return -3;
	btVector3 startvec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btVector3 endvec = btVector3((btScalar)XT, (btScalar)YT, (btScalar)ZT);
	btTransform start, end = btTransform::getIdentity();
	start.setOrigin(startvec);
	end.setOrigin(endvec);
	btCollisionWorld::ClosestConvexResultCallback callback(startvec, endvec);
	mabullet->World->convexSweepTest(convex, start, end, callback);
	if (callback.hasHit())
	{
		mabullet->HitResult.Position = callback.m_hitPointWorld;
		mabullet->HitResult.Normal = callback.m_hitNormalWorld;
		mabullet->HitResult.Fraction = callback.m_closestHitFraction;
		mabullet->HitResult.BodyID = callback.m_hitCollisionObject->getUserIndex();
		mabullet->HitResult.UserIndex = mabullet->Bodies[mabullet->HitResult.BodyID]->UserIndex;
		return 1;
	}
	return 0;
}

DLLEXPORT double MAB_WorldOverlap(double ShapeID, double X, double Y, double Z, double RX, double RY, double RZ, double RW, double Group, double Mask)
{
	if (!mabullet->worldExists()) return -1;
	if (!mabullet->shapeExists(ShapeID)) return -2;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	btCollisionObject* obj = new btCollisionObject();
	obj->setCollisionShape(mabullet->getShape(ShapeID));
	obj->setWorldTransform(trans);
	mabullet->World->addCollisionObject(obj, (short)Group, (short)Mask);
	mabullet->World->updateAabbs();
	MAOverlapCallback callback(obj);
	mabullet->OverlapResults.clear();
	mabullet->World->contactTest(obj, callback);
	mabullet->World->removeCollisionObject(obj);
	delete obj;
	return mabullet->OverlapResults.size();
}
