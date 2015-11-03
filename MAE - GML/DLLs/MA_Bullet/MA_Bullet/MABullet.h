#pragma once

#include <unordered_map>
#include <iostream>
#include <btBulletDynamicsCommon.h>

#define DLLEXPORT extern "C" __declspec (dllexport) double

struct MABullet {
	btBroadphaseInterface* Broadphase = nullptr;
	btDefaultCollisionConfiguration* CollisionConfiguration = nullptr;
	btCollisionDispatcher* Dispatcher = nullptr;
	btSequentialImpulseConstraintSolver* Solver = nullptr;
	btDiscreteDynamicsWorld* World = nullptr;

	btVector3 ReturnVec = btVector3(0.f, 0.f, 0.f);
	btQuaternion ReturnQuat = btQuaternion();

	std::unordered_map<int, btCollisionShape*> Shapes;
	int ShapeCount = 0;
	std::unordered_map<int, btRigidBody*> Bodies;
	int BodyCount = 0;

	inline bool worldExists() { return (World) ? true : false; };
	inline bool shapeExists(double ShapeID){ return (Shapes.count((int)ShapeID) > 0); };
	inline bool bodyExists(double BodyID){ return (Bodies.count((int)BodyID) > 0); };
	inline btCollisionShape* getShape(double ShapeID) { return Shapes[(int)ShapeID]; };
	inline btRigidBody* getBody(double BodyID) { return Bodies[(int)BodyID]; };
	inline double addShape(btCollisionShape* Shape) {
		Shapes[ShapeCount] = Shape;
		ShapeCount++;
		return ShapeCount - 1;
	}
	btVector3 toEuler(btMatrix3x3 &tm);

};

extern MABullet G;
