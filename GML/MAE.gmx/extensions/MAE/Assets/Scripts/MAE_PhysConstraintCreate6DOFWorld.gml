///MAE_PhysConstraintCreate6DOFWorld(body,transform,use_reference_frameA,disable_collision);

/**
 * Description:
 *   Creates a generic, 6 degrees of freedom constraint between two bodies or between a body and the world.
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
var quat = MAE_QuaternionCreateRotationMatrix(trans);

external_call(global._MAB_ConstraintParamTransform, 0, trans[12], trans[13], trans[14], quat[0], quat[1], quat[2], quat[3]);

return external_call(global._MAB_ConstraintCreate6DOF, argument0, 0, argument2, argument3);
