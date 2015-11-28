#include "MABullet.h"

btTransform ConstraintTransformA, ConstraintTransformB;

DLLEXPORT MAB_ConstraintCreateP2P(double BodyA, double AX, double AY, double AZ, double WorldA, double BodyB, double BX, double BY, double BZ, double WorldB, double DisableCollision)
{
	btPoint2PointConstraint* constraint;
	btVector3 pointA = btVector3((btScalar)AX, (btScalar)AY, (btScalar)AZ);
	btVector3 pointB = btVector3((btScalar)BX, (btScalar)BY, (btScalar)BZ);
	if(WorldA) pointA = G.getBody(BodyA)->getWorldTransform().inverse() * pointA;
	if(WorldB) pointB = G.getBody(BodyB)->getWorldTransform().inverse() * pointB;
	if (BodyB < 0) constraint = new btPoint2PointConstraint(*G.getBody(BodyA), pointA);
	else constraint = new btPoint2PointConstraint(*G.getBody(BodyA), *G.getBody(BodyB), pointA, pointB);
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateFixed(double BodyA, double BodyB)
{
	btFixedConstraint* constraint;
	btTransform trans = G.getBody(BodyA)->getWorldTransform().inverse() * G.getBody(BodyB)->getWorldTransform();
	constraint = new btFixedConstraint(*G.getBody(BodyA), *G.getBody(BodyB), btTransform::getIdentity(), trans.inverse());
	G.World->addConstraint(constraint, true);
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateSlider(double BodyA, double BodyB, double LinearReferenceFrameA, double DisableCollision)
{
	btSliderConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = G.getBody(BodyB);		
		constraint = new btSliderConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (LinearReferenceFrameA > 0));
	}
	else{
		constraint = new btSliderConstraint(*bodyA, ConstraintTransformA, (LinearReferenceFrameA > 0));
	}
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateGear(double BodyA, double BodyB, double AX, double AY, double AZ, double BX, double BY, double BZ, double Ratio, double DisableCollision)
{
	btGearConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	btRigidBody* bodyB = G.getBody(BodyB);
	btVector3 axisInA = btVector3((btScalar)AX, (btScalar)AY, (btScalar)AZ);
	btVector3 axisInB = btVector3((btScalar)BX, (btScalar)BY, (btScalar)BZ);
	constraint = new btGearConstraint(*bodyA, *bodyB, axisInA, axisInB, (btScalar)Ratio);
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateHinge(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	btHingeConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = G.getBody(BodyB);
		constraint = new btHingeConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btHingeConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreate6DOF(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	btGeneric6DofConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = G.getBody(BodyB);
		constraint = new btGeneric6DofConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btGeneric6DofConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateSpring6DOF(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	btGeneric6DofSpringConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = G.getBody(BodyB);
		constraint = new btGeneric6DofSpringConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btGeneric6DofSpringConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintCreateConeTwist(double BodyA, double BodyB, double DisableCollision)
{
	btConeTwistConstraint* constraint;
	btRigidBody* bodyA = G.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = G.getBody(BodyB);
		constraint = new btConeTwistConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB);
	}
	else {
		constraint = new btConeTwistConstraint(*bodyA, ConstraintTransformA);
	}
	G.World->addConstraint(constraint, (DisableCollision > 0));
	return G.addConstraint(constraint);
}

DLLEXPORT MAB_ConstraintParamTransform(double n, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	btVector3 vec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btQuaternion quat = btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW);	
	if(n == 0) ConstraintTransformA = btTransform(quat, vec);
	else ConstraintTransformB = btTransform(quat, vec);
	return 1;
}

enum PARAM {
	IMPULSE_CLAMP,
	DAMPING,
	TAU,
	PIVOTA,
	PIVOTB,
	BREAK_THRESHOLD,
};

DLLEXPORT MAB_ConstraintSetParam(double ConstraintID, double Param, double Value, double X, double Y, double Z)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	btTypedConstraint* constraint = G.getConstraint(ConstraintID);

	btPoint2PointConstraint* p2p              = dynamic_cast<btPoint2PointConstraint*>(constraint);
	btSliderConstraint* slider                = dynamic_cast<btSliderConstraint*>(constraint);
	btGearConstraint* gear                    = dynamic_cast<btGearConstraint*>(constraint);
	btHingeConstraint* hinge                  = dynamic_cast<btHingeConstraint*>(constraint);
	btGeneric6DofConstraint* generic6DOF      = dynamic_cast<btGeneric6DofConstraint*>(constraint);
	btGeneric6DofSpringConstraint* spring6DOF = dynamic_cast<btGeneric6DofSpringConstraint*>(constraint);
	btConeTwistConstraint* cone               = dynamic_cast<btConeTwistConstraint*>(constraint);

	btScalar value = (btScalar)Value;
	btVector3 vec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);

	switch ((int)Param)
	{
	case PARAM::IMPULSE_CLAMP:
		if (!p2p) return -2;
		p2p->m_setting.m_impulseClamp = value;
		break;
	case PARAM::DAMPING:
		if (!p2p) return -2;
		p2p->m_setting.m_damping = value;
		break;
	case PARAM::TAU:
		if (!p2p) return -2;
		p2p->m_setting.m_tau = value;
		break;
	case PARAM::PIVOTA:
		if (!p2p) return -2;
		p2p->setPivotA(vec);
		break;
	case PARAM::PIVOTB:
		if (!p2p) return -2;
		p2p->setPivotB(vec);
		break;
	case PARAM::BREAK_THRESHOLD:
		constraint->setBreakingImpulseThreshold(value);
		break;
	default:
		return -1;
	}
	return 1;
}

DLLEXPORT MAB_ConstraintSetEnabled(double ConstraintID, double enabled)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	if(enabled) G.getConstraint(ConstraintID)->setEnabled(true);
	G.getConstraint(ConstraintID)->setEnabled(false);
	return 1;
}

DLLEXPORT MAB_ConstraintGetAppliedImpulse(double ConstraintID)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	return G.getConstraint(ConstraintID)->getAppliedImpulse();
}

DLLEXPORT MAB_ConstraintDestroy(double ConstraintID)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	btTypedConstraint* constraint = G.getConstraint(ConstraintID);
	G.World->removeConstraint(constraint);
	G.Constraints.erase(constraint->getUserConstraintId());
	delete constraint;
	return 1;
}
