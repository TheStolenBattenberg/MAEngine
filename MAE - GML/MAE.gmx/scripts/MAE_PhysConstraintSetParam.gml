///MAE_PhysConstraintSetParam(constraint, param, values...)

/**
Sets a constraint parameter. All available params are listed below. Pass in a single real as the value unless otherwise specified.
Not all of them are tested. Param names match Bullet library function names. Please see the Bullet documentation for more information.

enum PARAM {
    BREAKING_IMPULSE_THRESHOLD,
    USE_FRAME_OFFSET,
    FRAMES,                              (matrix, matrix)
    SOLVER_ITERATIONS,
    P2P_IMPULSE_CLAMP,
    P2P_DAMPING,
    P2P_TAU,
    P2P_PIVOTA,                          (vector)
    P2P_PIVOTB,                          (vector)
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
    GEAR_AXIS_A,                        (vector)
    GEAR_AXIS_B,                        (vector)
    GEAR_RATIO,
    HINGE_ANGULAR_ONLY,
    HINGE_AXIS,                         (vector)
    HINGE_LIMITS,                       (low, high, softness, bias_factor, relaxation_factor)
    HINGE_MAX_MOTOR_IMPULSE,
    HINGE_MOTOR_TARGET,                 (targetAngle, dt)
    HINGE_MOTOR_ENABLED,
    DOF_ANGULAR_LOWER_LIMIT,            (vector)
    DOF_ANGULAR_UPPER_LIMIT,            (vector)
    DOF_AXIS,                           (vector, vector)
    DOF_LIMITS,                         (axis, lo, hi)
    DOF_LINEAR_LOWER_LIMIT,             (vector)
    DOF_LINEAR_UPPER_LIMIT,             (vector)
    DOF_SPRING_ENABLED,                 (axis, enabled)
    DOF_SPRING_DAMPING,                 (axis, damping)
    DOF_SPRING_STIFFNESS,               (axis, stiffness)
    CONE_ANGULAR_ONLY,
    CONE_DAMPING,
    CONE_FIX_THRESH,
    CONE_LIMITS,                        (swing_span1, swing_span2, twist_span, softness, biasFactor, relaxation_factor)
    CONE_MAX_MOTOR_IMPULSE,
    CONE_MAX_MOTOR_IMPULSE_NORMALIZED,
    CONE_MOTOR_TARGET,                  (quaternion)
    CONE_MOTOR_TARGET_CONSTRAINT_SPACE, (quaternion)
    CONE_MOTOR_ENABLED,
}
*/

if(argument_count == 3){
    if(MAE_VectorIsVec3(argument[2])){
        var vec = argument[2];
        return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], vec[0], vec[1], vec[2], 0, 0, 0);
    }
    if(MAE_QuaternionIsQuaternion(argument[2])){
        var quat = argument[2];
        external_call(global.MAB_ConstraintParamTransform, 0, 0, 0, 0, quat[0], quat[1], quat[2], quat[3]);
        return external_call(global.MAV_ConstraintSetParam, argument[0], argument[1], 0, 0, 0, 0, 0, 0);
    }
    return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], 0, 0, 0, 0, 0);
}
if(argument_count == 4){
    if(MAE_VectorIsVec3(argument[2]) && MAE_VectorIsVec3(argument[3])){
        vec1 = argument[2];
        vec2 = argument[3];
        return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], vec1[0], vec1[1], vec1[2], vec2[0], vec2[1], vec2[2]);
    }
    if(MAE_MatrixIsMat4(argument[2]) && MAE_MatrixIsMat4(argument[3])){
        var trans1 = argument[2];
        var quat1 = MAE_QuaternionCreateRotationMatrix(trans1);
        external_call(global.MAB_ConstraintParamTransform, 0, trans1[12], trans1[13], trans1[14], quat1[0], quat1[1], quat1[2], quat1[3]);
        var trans2 = argument[3];
        var quat2 = MAE_QuaternionCreateRotationMatrix(trans2);
        external_call(global.MAB_ConstraintParamTransform, 0, trans2[12], trans2[13], trans2[14], quat2[0], quat2[1], quat2[2], quat2[3]);
        return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], 0, 0, 0, 0, 0, 0);
    }
    return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], 0, 0, 0, 0);
}
if(argument_count == 5) return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], 0, 0, 0);
if(argument_count == 6) return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], 0, 0);
if(argument_count == 7) return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], 0);
if(argument_count == 8) return external_call(global.MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], argument[7]);

