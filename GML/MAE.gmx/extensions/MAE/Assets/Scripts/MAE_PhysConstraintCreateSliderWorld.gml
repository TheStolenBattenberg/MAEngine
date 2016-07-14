///MAE_PhysConstraintCreateSliderWorld(body,transform,use_linear_reference_frame);

/**
 * Description:
 *   Creates a slider constraint between two bodies or between a body and the world.
 *
 * Arguments:
 *   [1] - BodyA
 *   [2] - TransformA matrix
 *   [3] - BodyB
 *   [4] - TransformB matrix
 *   [5] - Use linear reference frame A?
 *   [6] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var trans = argument1;
var quat = MAE_QuaternionCreateRotationMatrix(trans1);

external_call(global._MAB_ConstraintParamTransform, 0, trans[12], trans[13], trans[14], quat[0], quat[1], quat[2], quat[3]);

return external_call(global._MAB_ConstraintCreateSlider, argument0, 0, argument2, true);
