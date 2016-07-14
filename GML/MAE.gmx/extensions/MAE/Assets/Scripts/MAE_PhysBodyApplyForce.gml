///MAE_PhysBodyApplyForce(body,position,force);

/**
 * Description:
 *   Applies a force to a physics body at the specified point in local space.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Position as a vector
 *   [3] - Force as a vector
 *
 * Returns:
 *   Success
 */

var position = argument1, force = argument2;

return external_call(global._MAB_BodyApplyForce, argument0, position[0], position[1], position[2], force[0], force[1], force[2]);
