#include <MAE/Bullet/Bullet.h>
#include <MAE/Main.h>

#include <GMLAPI/Main.h>

btTransform ConstraintTransformA, ConstraintTransformB;

DLLEXPORT double MAB_ConstraintCreateP2P(double BodyA, double AX, double AY, double AZ, double WorldA, double BodyB, double BX, double BY, double BZ, double WorldB, double DisableCollision)
{
	TRYBEG();
	btPoint2PointConstraint* constraint;
	btVector3 pointA = btVector3((btScalar)AX, (btScalar)AY, (btScalar)AZ);
	btVector3 pointB = btVector3((btScalar)BX, (btScalar)BY, (btScalar)BZ);
	if(WorldA) pointA = mabullet.getBody(BodyA)->getWorldTransform().inverse() * pointA;
	if(WorldB) pointB = mabullet.getBody(BodyB)->getWorldTransform().inverse() * pointB;
	if (BodyB < 0) constraint = new btPoint2PointConstraint(*mabullet.getBody(BodyA), pointA);
	else constraint = new btPoint2PointConstraint(*mabullet.getBody(BodyA), *mabullet.getBody(BodyB), pointA, pointB);
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateFixed(double BodyA, double BodyB)
{
	TRYBEG();
	btFixedConstraint* constraint;
	btTransform trans = mabullet.getBody(BodyA)->getWorldTransform().inverse() * mabullet.getBody(BodyB)->getWorldTransform();
	constraint = new btFixedConstraint(*mabullet.getBody(BodyA), *mabullet.getBody(BodyB), btTransform::getIdentity(), trans.inverse());
	mabullet.world->addConstraint(constraint, true);
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateSlider(double BodyA, double BodyB, double LinearReferenceFrameA, double DisableCollision)
{
	TRYBEG();
	btSliderConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = mabullet.getBody(BodyB);		
		constraint = new btSliderConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (LinearReferenceFrameA > 0));
	}
	else{
		constraint = new btSliderConstraint(*bodyA, ConstraintTransformA, (LinearReferenceFrameA > 0));
	}
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateGear(double BodyA, double BodyB, double AX, double AY, double AZ, double BX, double BY, double BZ, double Ratio, double DisableCollision)
{
	TRYBEG();
	btGearConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	btRigidBody* bodyB = mabullet.getBody(BodyB);
	btVector3 axisInA = btVector3((btScalar)AX, (btScalar)AY, (btScalar)AZ);
	btVector3 axisInB = btVector3((btScalar)BX, (btScalar)BY, (btScalar)BZ);
	constraint = new btGearConstraint(*bodyA, *bodyB, axisInA, axisInB, (btScalar)Ratio);
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateHinge(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	TRYBEG();
	btHingeConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = mabullet.getBody(BodyB);
		constraint = new btHingeConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btHingeConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreate6DOF(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	TRYBEG();
	btGeneric6DofConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = mabullet.getBody(BodyB);
		constraint = new btGeneric6DofConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btGeneric6DofConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateSpring6DOF(double BodyA, double BodyB, double UseReferenceFrameA, double DisableCollision)
{
	TRYBEG();
	btGeneric6DofSpringConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = mabullet.getBody(BodyB);
		constraint = new btGeneric6DofSpringConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB, (UseReferenceFrameA > 0));
	}
	else {
		constraint = new btGeneric6DofSpringConstraint(*bodyA, ConstraintTransformA, (UseReferenceFrameA > 0));
	}
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintCreateConeTwist(double BodyA, double BodyB, double DisableCollision)
{
	TRYBEG();
	btConeTwistConstraint* constraint;
	btRigidBody* bodyA = mabullet.getBody(BodyA);
	if (BodyB > 0) {
		btRigidBody* bodyB = mabullet.getBody(BodyB);
		constraint = new btConeTwistConstraint(*bodyA, *bodyB, ConstraintTransformA, ConstraintTransformB);
	}
	else {
		constraint = new btConeTwistConstraint(*bodyA, ConstraintTransformA);
	}
	mabullet.world->addConstraint(constraint, (DisableCollision > 0));
	return mabullet.addConstraint(constraint);
	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintParamTransform(double n, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	TRYBEG();
	btVector3 vec = btVector3((btScalar)X, (btScalar)Y, (btScalar)Z);
	btQuaternion quat = btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW);	
	if(n == 0) ConstraintTransformA = btTransform(quat, vec);
	else ConstraintTransformB = btTransform(quat, vec);
	return 1;
	TRYEND(0);
}

enum PARAM {
	BREAKING_IMPULSE_THRESHOLD,
	USE_FRAME_OFFSET,
	FRAMES,
	SOLVER_ITERATIONS,
	P2P_IMPULSE_CLAMP,
	P2P_DAMPING,
	P2P_TAU,
	P2P_PIVOTA,
	P2P_PIVOTB,
	SLIDER_DAMPING_DIR_ANG,
	SLIDER_DAMPING_DIR_LIN,
	SLIDER_DAMPING_LIM_ANG,
	SLIDER_DAMPING_LIM_LIN,
	SLIDER_DAMPING_ORTHO_ANG,
	SLIDER_DAMPING_ORTHO_LIN,
	SLIDER_LOWER_ANG_LIMIT,
	SLIDER_LOWER_LIN_LIMIT,
	SLIDER_MAX_ANG_MOTOR_FORCE,
	SLIDER_MAX_LIN_MOTOR_FORCE,
	SLIDER_POWERED_ANG_MOTOR,
	SLIDER_POWERED_LIN_MOTOR,
	SLIDER_RESTITUTION_DIR_ANG,
	SLIDER_RESTITUTION_DIR_LIN,
	SLIDER_RESTITUTION_LIM_ANG,
	SLIDER_RESTITUTION_LIM_LIN,
	SLIDER_RESTITUTION_ORTHO_ANG,
	SLIDER_RESTITUTION_ORTHO_LIN,
	SLIDER_SOFTNESS_DIR_ANG,
	SLIDER_SOFTNESS_DIR_LIN,
	SLIDER_SOFTNESS_LIM_ANG,
	SLIDER_SOFTNESS_LIM_LIN,
	SLIDER_SOFTNESS_ORTHO_ANG,
	SLIDER_SOFTNESS_ORTHO_LIN,
	SLIDER_TARGET_ANG_MOTOR_VELOCITY,
	SLIDER_TARGET_LIN_MOTOR_VELOCITY,
	SLIDER_UPPER_ANG_LIMIT,
	SLIDER_UPPER_LIN_LIMIT,
	GEAR_AXIS_A,
	GEAR_AXIS_B,
	GEAR_RATIO,
	HINGE_ANGULAR_ONLY,
	HINGE_AXIS,
	HINGE_LIMITS,
	HINGE_MAX_MOTOR_IMPULSE,
	HINGE_MOTOR_TARGET,
	HINGE_MOTOR_ENABLED,
	DOF_ANGULAR_LOWER_LIMIT,
	DOF_ANGULAR_UPPER_LIMIT,
	DOF_AXIS,
	DOF_LIMITS,
	DOF_LINEAR_LOWER_LIMIT,
	DOF_LINEAR_UPPER_LIMIT,
	DOF_SPRING_ENABLED,
	DOF_SPRING_DAMPING,
	DOF_SPRING_STIFFNESS,
	CONE_ANGULAR_ONLY,
	CONE_DAMPING,
	CONE_FIX_THRESH,
	CONE_LIMITS,
	CONE_MAX_MOTOR_IMPULSE,
	CONE_MAX_MOTOR_IMPULSE_NORMALIZED,
	CONE_MOTOR_TARGET,
	CONE_MOTOR_TARGET_CONSTRAINT_SPACE,
	CONE_MOTOR_ENABLED,
};

DLLEXPORT double MAB_ConstraintSetParam(double ConstraintID, double Param, double Value, double Value2, double Value3, double Value4, double Value5, double Value6)
{
	TRYBEG();
	if (!mabullet.constraintExists(ConstraintID)) return 0;
	btTypedConstraint* constraint = mabullet.getConstraint(ConstraintID);

	btPoint2PointConstraint* p2p              = dynamic_cast<btPoint2PointConstraint*>(constraint);
	btSliderConstraint* slider                = dynamic_cast<btSliderConstraint*>(constraint);
	btGearConstraint* gear                    = dynamic_cast<btGearConstraint*>(constraint);
	btHingeConstraint* hinge                  = dynamic_cast<btHingeConstraint*>(constraint);
	btGeneric6DofConstraint* generic6DOF      = dynamic_cast<btGeneric6DofConstraint*>(constraint);
	btGeneric6DofSpringConstraint* spring6DOF = dynamic_cast<btGeneric6DofSpringConstraint*>(constraint);
	btConeTwistConstraint* cone               = dynamic_cast<btConeTwistConstraint*>(constraint);

	btScalar value  = (btScalar)Value;
	btScalar value2 = (btScalar)Value2;
	btScalar value3 = (btScalar)Value3;
	btScalar value4 = (btScalar)Value4;
	btScalar value5 = (btScalar)Value5;
	btScalar value6 = (btScalar)Value6;
	btVector3 vec = btVector3(value, value2, value3);
	btVector3 vec2 = btVector3(value4, value5, value6);

	switch ((int)Param)
	{
	case PARAM::BREAKING_IMPULSE_THRESHOLD:
		constraint->setBreakingImpulseThreshold(value);
		break;
	case PARAM::USE_FRAME_OFFSET:
		if (slider) slider->setUseFrameOffset((value > 0));
		else if (generic6DOF) generic6DOF->setUseFrameOffset((value > 0));
		else if (spring6DOF) spring6DOF->setUseFrameOffset((value > 0));
		else if (hinge) hinge->setUseFrameOffset((value > 0));
		else return -2;
		break;
	case PARAM::FRAMES:
		if (slider) slider->setFrames(ConstraintTransformA, ConstraintTransformB);
		else if (generic6DOF) generic6DOF->setFrames(ConstraintTransformA, ConstraintTransformB);
		else if (spring6DOF) spring6DOF->setFrames(ConstraintTransformA, ConstraintTransformB);
		else if (hinge) hinge->setFrames(ConstraintTransformA, ConstraintTransformB);
		else return -2;
		break;
	case PARAM::SOLVER_ITERATIONS:
		constraint->setOverrideNumSolverIterations((int)value);
		break;
	case PARAM::P2P_IMPULSE_CLAMP:
		if (!p2p) return -2;
		p2p->m_setting.m_impulseClamp = value;
		break;
	case PARAM::P2P_DAMPING:
		if (!p2p) return -2;
		p2p->m_setting.m_damping = value;
		break;
	case PARAM::P2P_TAU:
		if (!p2p) return -2;
		p2p->m_setting.m_tau = value;
		break;
	case PARAM::P2P_PIVOTA:
		if (!p2p) return -2;
		p2p->setPivotA(vec);
		break;
	case PARAM::P2P_PIVOTB:
		if (!p2p) return -2;
		p2p->setPivotB(vec);
		break;
	case PARAM::SLIDER_DAMPING_DIR_ANG:
		if (!slider) return -2;
		slider->setDampingDirAng(value);
		break;
	case PARAM::SLIDER_DAMPING_DIR_LIN:
		if (!slider) return -2;
		slider->setDampingDirLin(value);
		break;
	case PARAM::SLIDER_DAMPING_LIM_ANG:
		if (!slider) return -2;
		slider->setDampingLimAng(value);
		break;
	case PARAM::SLIDER_DAMPING_LIM_LIN:
		if (!slider) return -2;
		slider->setDampingLimLin(value);
		break;
	case PARAM::SLIDER_DAMPING_ORTHO_ANG:
		if (!slider) return -2;
		slider->setDampingOrthoAng(value);
		break;
	case PARAM::SLIDER_DAMPING_ORTHO_LIN:
		if (!slider) return -2;
		slider->setDampingOrthoLin(value);
		break;
	case PARAM::SLIDER_LOWER_ANG_LIMIT:
		if (!slider) return -2;
		slider->setLowerAngLimit(value);
		break;
	case PARAM::SLIDER_LOWER_LIN_LIMIT:
		if (!slider) return -2;
		slider->setLowerLinLimit(value);
		break;
	case PARAM::SLIDER_MAX_ANG_MOTOR_FORCE:
		if (!slider) return -2;
		slider->setMaxAngMotorForce(value);
		break;
	case PARAM::SLIDER_MAX_LIN_MOTOR_FORCE:
		if (!slider) return -2;
		slider->setMaxLinMotorForce(value);
		break;
	case PARAM::SLIDER_POWERED_ANG_MOTOR:
		if (!slider) return -2;
		slider->setPoweredAngMotor((value > 0));
		break;
	case PARAM::SLIDER_POWERED_LIN_MOTOR:
		if (!slider) return -2;
		slider->setPoweredLinMotor((value > 0));
		break;
	case PARAM::SLIDER_RESTITUTION_DIR_ANG:
		if (!slider) return -2;
		slider->setRestitutionDirAng(value);
		break;
	case PARAM::SLIDER_RESTITUTION_DIR_LIN:
		if (!slider) return -2;
		slider->setRestitutionDirLin(value);
		break;
	case PARAM::SLIDER_RESTITUTION_LIM_ANG:
		if (!slider) return -2;
		slider->setRestitutionLimAng(value);
		break;
	case PARAM::SLIDER_RESTITUTION_LIM_LIN:
		if (!slider) return -2;
		slider->setRestitutionLimLin(value);
		break;
	case PARAM::SLIDER_RESTITUTION_ORTHO_ANG:
		if (!slider) return -2;
		slider->setRestitutionOrthoAng(value);
		break;
	case PARAM::SLIDER_RESTITUTION_ORTHO_LIN:
		if (!slider) return -2;
		slider->setRestitutionOrthoLin(value);
		break;
	case PARAM::SLIDER_SOFTNESS_DIR_ANG:
		if (!slider) return -2;
		slider->setSoftnessDirAng(value);
		break;
	case PARAM::SLIDER_SOFTNESS_DIR_LIN:
		if (!slider) return -2;
		slider->setSoftnessDirLin(value);
		break;
	case PARAM::SLIDER_SOFTNESS_LIM_ANG:
		if (!slider) return -2;
		slider->setSoftnessLimAng(value);
		break;
	case PARAM::SLIDER_SOFTNESS_LIM_LIN:
		if (!slider) return -2;
		slider->setSoftnessLimLin(value);
		break;
	case PARAM::SLIDER_SOFTNESS_ORTHO_ANG:
		if (!slider) return -2;
		slider->setSoftnessOrthoAng(value);
		break;
	case PARAM::SLIDER_SOFTNESS_ORTHO_LIN:
		if (!slider) return -2;
		slider->setSoftnessOrthoLin(value);
		break;
	case PARAM::SLIDER_TARGET_ANG_MOTOR_VELOCITY:
		if (!slider) return -2;
		slider->setTargetAngMotorVelocity(value);
		break;
	case PARAM::SLIDER_TARGET_LIN_MOTOR_VELOCITY:
		if (!slider) return -2;
		slider->setTargetLinMotorVelocity(value);
		break;
	case PARAM::SLIDER_UPPER_ANG_LIMIT:
		if (!slider) return -2;
		slider->setUpperAngLimit(value);
		break;
	case PARAM::SLIDER_UPPER_LIN_LIMIT:
		if (!slider) return -2;
		slider->setUpperLinLimit(value);
		break;
	case PARAM::GEAR_AXIS_A:
		if (!gear) return -2;
		gear->setAxisA(vec);
		break;
	case PARAM::GEAR_AXIS_B:
		if (!gear) return -2;
		gear->setAxisB(vec);
		break;
	case PARAM::GEAR_RATIO:
		if (!gear) return -2;
		gear->setRatio(value);
		break;
	case PARAM::HINGE_ANGULAR_ONLY:
		if (!hinge) return -2;
		hinge->setAngularOnly((value > 0));
		break;
	case PARAM::HINGE_AXIS:
		if (!hinge) return -2;
		hinge->setAxis(vec);
		break;
	case PARAM::HINGE_LIMITS:
		if (!hinge) return -2;
		hinge->setLimit(value, value2, value3, value4, value5);
		break;
	case PARAM::HINGE_MAX_MOTOR_IMPULSE:
		if (!hinge) return -2;
		hinge->setMaxMotorImpulse(value);
		break;
	case PARAM::HINGE_MOTOR_TARGET:
		if (!hinge) return -2;
		hinge->setMotorTarget(value, value2);
		break;
	case PARAM::HINGE_MOTOR_ENABLED:
		if (!hinge) return -2;
		hinge->enableMotor(value > 0);
	case PARAM::DOF_ANGULAR_LOWER_LIMIT:
		if (generic6DOF) generic6DOF->setAngularLowerLimit(vec);
		else if (spring6DOF) spring6DOF->setAngularLowerLimit(vec);
		else return -2;
		break;
	case PARAM::DOF_ANGULAR_UPPER_LIMIT:
		if (generic6DOF) generic6DOF->setAngularUpperLimit(vec);
		else if (spring6DOF) spring6DOF->setAngularUpperLimit(vec);
		else return -2;
		break;
	case PARAM::DOF_AXIS:
		if (generic6DOF) generic6DOF->setAxis(vec, vec2);
		else if (spring6DOF) spring6DOF->setAxis(vec, vec2);
		else return -2;
		break;
	case PARAM::DOF_LIMITS:
		if (generic6DOF) generic6DOF->setLimit((int)value, value2, value3);
		else if (spring6DOF) spring6DOF->setLimit((int)value, value2, value3);
		else return -2;
		break;
	case PARAM::DOF_LINEAR_LOWER_LIMIT:
		if (generic6DOF) generic6DOF->setLinearLowerLimit(vec);
		else if (spring6DOF) spring6DOF->setLinearLowerLimit(vec);
		else return -2;
		break;
	case PARAM::DOF_LINEAR_UPPER_LIMIT:
		if (generic6DOF) generic6DOF->setLinearUpperLimit(vec);
		else if (spring6DOF) spring6DOF->setLinearUpperLimit(vec);
		else return -2;
		break;
	case PARAM::DOF_SPRING_DAMPING:
		if (!spring6DOF) return -2;
		spring6DOF->setDamping((int)value, value2);
		break;
	case PARAM::DOF_SPRING_STIFFNESS:
		if (!spring6DOF) return -2;
		spring6DOF->setStiffness((int)value, value2);
		break;
	case PARAM::DOF_SPRING_ENABLED:
		if (!spring6DOF) return -2;
		spring6DOF->enableSpring((int)value, (value2 > 0));
		break;
	case PARAM::CONE_ANGULAR_ONLY:
		if (!cone) return -2;
		cone->setAngularOnly((value > 0));
		break;
	case PARAM::CONE_DAMPING:
		if (!cone) return -2;
		cone->setDamping(value);
		break;
	case PARAM::CONE_FIX_THRESH:
		if (!cone) return -2;
		cone->setFixThresh(value);
		break;
	case PARAM::CONE_LIMITS:
		if (!cone) return -2;
		cone->setLimit(value, value2, value3, value4, value5, value6);
		break;
	case PARAM::CONE_MAX_MOTOR_IMPULSE:
		if (!cone) return -2;
		cone->setMaxMotorImpulse(value);
		break;
	case PARAM::CONE_MAX_MOTOR_IMPULSE_NORMALIZED:
		if (!cone) return -2;
		cone->setMaxMotorImpulseNormalized(value);
		break;
	case PARAM::CONE_MOTOR_TARGET:
		if (!cone) return -2;
		cone->setMotorTarget(ConstraintTransformA.getRotation());
		break;
	case PARAM::CONE_MOTOR_TARGET_CONSTRAINT_SPACE:
		if (!cone) return -2;
		cone->setMotorTargetInConstraintSpace(ConstraintTransformA.getRotation());
		break;
	case PARAM::CONE_MOTOR_ENABLED:
		if (!cone) return -2;
		cone->enableMotor((value > 0));
		break;
	default:
		return -1;
	}
	return 1;

	TRYEND(-1);
}

DLLEXPORT double MAB_ConstraintSetEnabled(double ConstraintID, double enabled)
{
	TRYBEG();
	if (!mabullet.constraintExists(ConstraintID)) return 0;
	if(enabled) mabullet.getConstraint(ConstraintID)->setEnabled(true);
	mabullet.getConstraint(ConstraintID)->setEnabled(false);
	return 1;
	TRYEND(0);
}

DLLEXPORT double MAB_ConstraintGetAppliedImpulse(double ConstraintID)
{
	TRYBEG();
	if (!mabullet.constraintExists(ConstraintID)) return 0;
	return mabullet.getConstraint(ConstraintID)->getAppliedImpulse();
	TRYEND(0);
}

DLLEXPORT double MAB_ConstraintDestroy(double ConstraintID)
{
	TRYBEG();
	if (!mabullet.constraintExists(ConstraintID)) return 0;
	btTypedConstraint* constraint = mabullet.getConstraint(ConstraintID);
	mabullet.world->removeConstraint(constraint);
	mabullet.constraints.erase(constraint->getUserConstraintId());
	delete constraint;
	return 1;
	TRYEND(0);
}
