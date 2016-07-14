///MAE_PhysConstraintCreateConeTwistWorld(body,transform,disable_collision);

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

var trans = argument1;
var quat = MAE_QuaternionCreateRotationMatrix(trans);

external_call(global._MAB_ConstraintParamTransform, 0, trans[12], trans[13], trans[14], quat[0], quat[1], quat[2], quat[3]);

return external_call(global._MAB_ConstraintCreateConeTwist, argument0, 0, argument2);
