#include "MABullet.h"

DLLEXPORT MAB_ConstraintCreateP2P(double BodyA, double AX, double AY, double AZ, double WorldA, double BodyB, double BX, double BY, double BZ, double WorldB)
{
	btPoint2PointConstraint* constraint;
	btVector3 pointA = btVector3((btScalar)AX, (btScalar)AY, (btScalar)AZ);
	btVector3 pointB = btVector3((btScalar)BX, (btScalar)BY, (btScalar)BZ);
	if(WorldA) pointA = G.getBody(BodyA)->getWorldTransform().inverse() * pointA;
	if(WorldB) pointB = G.getBody(BodyB)->getWorldTransform().inverse() * pointB;
	if (BodyB < 0) constraint = new btPoint2PointConstraint(*G.getBody(BodyA), pointA);
	else constraint = new btPoint2PointConstraint(*G.getBody(BodyA), *G.getBody(BodyB), pointA, pointB);
	constraint->m_setting.m_impulseClamp = 5.f;
	constraint->m_setting.m_tau = 0.001f;
	G.World->addConstraint(constraint, false);
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

DLLEXPORT MAB_ConstraintSetPivot(double ConstraintID, double n, double X, double Y, double Z)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	btPoint2PointConstraint* p2p = dynamic_cast<btPoint2PointConstraint*>(G.getConstraint(ConstraintID));
	if (!p2p) return -1;
	if (n > 0) p2p->setPivotB(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	else p2p->setPivotA(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}

DLLEXPORT MAB_ConstraintSetBreakThreshold(double ConstraintID, double threshold)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	G.getConstraint(ConstraintID)->setBreakingImpulseThreshold((btScalar)threshold);
	return 1;
}

DLLEXPORT MAB_ConstraintSetEnabled(double ConstraintID, double enabled)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	if(enabled) G.getConstraint(ConstraintID)->setEnabled(true);
	G.getConstraint(ConstraintID)->setEnabled(false);
	return 1;
}

DLLEXPORT MAB_ConstraintDestroy(double ConstraintID)
{
	if (!G.constraintExists(ConstraintID)) return 0;
	G.World->removeConstraint(G.getConstraint(ConstraintID));
	delete G.getConstraint(ConstraintID);
	return 1;
}
