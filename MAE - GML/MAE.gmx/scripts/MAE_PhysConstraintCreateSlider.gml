///MAE_PhysConstraintCreateSlider(bodyA, transformA, bodyB, transformB, use_linear_reference_frameA, disable_collision)
///MAE_PhysConstraintCreateSlider(bodyA, transformA, use_linear_reference_frameA)

/**
 * Description:
 *   Creates a slider constraint between two bodies or between a body and the world.
 *
 * Arguments:
 *   [0] - BodyA
 *   [1] - TransformA matrix
 *   [2] - BodyB
 *   [3] - TransformB matrix
 *   [4] - Use linear reference frame A?
 *   [5] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var trans1 = argument[1];
var quat1 = MAE_QuaternionCreateRotationMatrix(trans1);
external_call(global.MAB_ConstraintParamTransform, 0, trans1[12], trans1[13], trans1[14], quat1[0], quat1[1], quat1[2], quat1[3]);

if(argument_count == 3) return external_call(global.MAB_ConstraintCreateSlider, argument[0], 0, argument[2], true);

var trans2 = argument[3];
var quat2 = MAE_QuaternionCreateRotationMatrix(trans2);
external_call(global.MAB_ConstraintParamTransform, 1, trans2[12], trans2[13], trans2[14], quat2[0], quat2[1], quat2[2], quat2[3]);

return external_call(global.MAB_ConstraintCreateSlider, argument[0], argument[2], argument[4], argument[5]);

