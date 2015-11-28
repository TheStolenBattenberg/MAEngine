///MAE_PhysConstraintCreateSpring6DOF(bodyA, transformA, bodyB, transformB, use_reference_frameA, disable_collision)
///MAE_PhysConstraintCreateSpring6DOF(bodyA, transformA, use_reference_frameA, disable_collision)
/*
Creates a generic 6DOF spring constraint. The second body is optional, and if left out the constraint will attach to the world instead.
transformA and transformB are matrices.
*/

var trans1 = argument[1];
var quat1 = MAE_QuaternionCreateRotationMatrix(trans1);
external_call(global.MAB_ConstraintParamTransform, trans1[12], trans1[13], trans1[14], quat1[0], quat1[1], quat1[2], quat1[3]);

if(argument_count == 4) return external_call(global.MAB_ConstraintCreateSpring6DOF, argument[0], 0, argument[2], argument[3]);

var trans2 = argument[3];
var quat2 = MAE_QuaternionCreateRotationMatrix(trans2);
external_call(global.MAB_ConstraintParamTransform, trans2[12], trans2[13], trans2[14], quat2[0], quat2[1], quat2[2], quat2[3]);

return external_call(global.MAB_ConstraintCreateSpring6DOF, argument[0], argument[2], argument[4], argument[5]);

