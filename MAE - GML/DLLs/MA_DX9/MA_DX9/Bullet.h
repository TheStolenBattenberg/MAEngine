#pragma once

#include <unordered_map>
#include <btBulletDynamicsCommon.h>

struct MABody
{
	btRigidBody* Body;
	unsigned int UserIndex;

	MABody(btRigidBody* Body) : Body(Body) {}
};

struct MAHitPoint
{
	btVector3 Position;
	btVector3 Normal;
	btScalar Fraction;
	int BodyID;
	int UserIndex;
};

ATTRIBUTE_ALIGNED16(struct) MABullet {

	BT_DECLARE_ALIGNED_ALLOCATOR();

	btBroadphaseInterface* Broadphase = nullptr;
	btDefaultCollisionConfiguration* CollisionConfiguration = nullptr;
	btCollisionDispatcher* Dispatcher = nullptr;
	btSequentialImpulseConstraintSolver* Solver = nullptr;
	btDiscreteDynamicsWorld* World = nullptr;
	btIDebugDraw* DebugDrawer = nullptr;

	bool UseMotionState;

	btVector3 ReturnVec;
	btQuaternion ReturnQuat;
	MAHitPoint HitResult;
	std::vector<int> OverlapResults;

	std::unordered_map<int, btCollisionShape*> Shapes;
	int ShapeCount = 0;
	std::unordered_map<int, MABody*> Bodies;
	int BodyCount = 0;
	std::unordered_map<int, btTypedConstraint*> Constraints;
	int ConstraintCount = 0;

	inline bool worldExists() const { return (World != nullptr); }
	inline bool shapeExists(double ShapeID) const { return (Shapes.count((int)ShapeID) > 0); }
	inline bool bodyExists(double BodyID) const { return (Bodies.count((int)BodyID) > 0); }
	inline bool constraintExists(double ConstraintID) const { return (Constraints.count((int)ConstraintID) > 0); }
	inline btCollisionShape* getShape(double ShapeID) { return Shapes[(int)ShapeID]; }
	inline btRigidBody* getBody(double BodyID) { return Bodies[(int)BodyID]->Body; }
	inline btTypedConstraint* getConstraint(double ConstraintID) { return Constraints[(int)ConstraintID]; }
	double addShape(btCollisionShape* Shape);
	double addConstraint(btTypedConstraint* Constraint);
	bool destroyWorld();
	static btVector3 toEuler(btMatrix3x3 &tm);

	~MABullet();
};

extern MABullet* mabullet;

struct MAOverlapCallback : public btCollisionWorld::ContactResultCallback {
	MAOverlapCallback(btCollisionObject* tgtBody) : btCollisionWorld::ContactResultCallback(), body(tgtBody) {};
	btCollisionObject* body;
	bool hasHit = false;
	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0, int partId0, int index0, const btCollisionObjectWrapper* colObj1, int partId1, int index1) {
		if (colObj0->m_collisionObject == body) {
			hasHit = true;
			mabullet->OverlapResults.push_back(colObj1->m_collisionObject->getUserIndex());
		}
		return 0;
	}
};
