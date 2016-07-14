///MAE_PhysConstraintCreateConeTwist(bodyA,transformA,bodyB,transformB,disable_collision);

/**
 * Description:
 *   
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   [-]
 */

var trans1 = argument1, trans2 = argument3;

var quat1 = MAE_QuaternionCreateRotationMatrix(trans1);
var quat2 = MAE_QuaternionCreateRotationMatrix(trans2);

external_call(global._MAB_ConstraintParamTransform, 0, trans1[12], trans1[13], trans1[14], quat1[0], quat1[1], quat1[2], quat1[3]);
external_call(global._MAB_ConstraintParamTransform, 1, trans2[12], trans2[13], trans2[14], quat2[0], quat2[1], quat2[2], quat2[3]);

return external_call(global._MAB_ConstraintCreateConeTwist, argument0, argument2, argument4);
