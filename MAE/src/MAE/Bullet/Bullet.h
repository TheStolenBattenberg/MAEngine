#pragma once

#include <unordered_map>
#include <btBulletDynamicsCommon.h>

struct RigidBody {
	btRigidBody* body;
	unsigned int userIndex;

	RigidBody(btRigidBody* body) : body(body) {}
};

struct HitResult {
	btVector3 position;
	btVector3 normal;
	btScalar fraction;
	int bodyID;
	int userIndex;
};

struct MABullet {
	btBroadphaseInterface* broadphase = nullptr;
	btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btSequentialImpulseConstraintSolver* solver = nullptr;
	btDiscreteDynamicsWorld* world = nullptr;
	btIDebugDraw* debugDrawer = nullptr;

	bool useMotionState;

	btVector3 returnVec;
	btQuaternion returnQuat;
	HitResult hitResult;
	std::vector<int> overlapIDs;

	std::unordered_map<int, btCollisionShape*> shapes;
	int shapeCount = 0;
	std::unordered_map<int, RigidBody*> bodies;
	int bodyCount = 0;
	std::unordered_map<int, btTypedConstraint*> constraints;
	int constraintCount = 0;

	inline bool worldExists() const { return (world != nullptr); }
	inline bool shapeExists(double ShapeID) const { return (shapes.count((int)ShapeID) > 0); }
	inline bool bodyExists(double BodyID) const { return (bodies.count((int)BodyID) > 0); }
	inline bool constraintExists(double ConstraintID) const { return (constraints.count((int)ConstraintID) > 0); }
	inline btCollisionShape* getShape(double ShapeID) { return shapes[(int)ShapeID]; }
	inline btRigidBody* getBody(double BodyID) { return bodies[(int)BodyID]->body; }
	inline btTypedConstraint* getConstraint(double ConstraintID) { return constraints[(int)ConstraintID]; }
	double addShape(btCollisionShape* Shape);
	double addConstraint(btTypedConstraint* Constraint);
	bool destroyWorld();
	static btVector3 toEuler(btMatrix3x3 &tm);
};

extern MABullet mabullet;

struct MAOverlapCallback : public btCollisionWorld::ContactResultCallback {
	MAOverlapCallback(btCollisionObject* tgtBody) : btCollisionWorld::ContactResultCallback(), body(tgtBody) {};
	btCollisionObject* body;
	bool hasHit = false;
	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0, int partId0, int index0, const btCollisionObjectWrapper* colObj1, int partId1, int index1) {
		if (colObj0->m_collisionObject == body) {
			hasHit = true;
			mabullet.overlapIDs.push_back(colObj1->m_collisionObject->getUserIndex());
		}
		return 0;
	}
};
