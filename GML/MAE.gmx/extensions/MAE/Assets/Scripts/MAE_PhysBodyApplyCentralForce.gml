///MAE_PhysBodyApplyCentralForce(body,relative,force);

/**
 * Description:
 *   Applies a force to the center of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Local space(true), or world space(false)
 *   [3] - Force as a vector
 *
 * Returns:
 *   Success
 */

var force = argument2;

return external_call(global._MAB_BodyApplyCentralForce, argument0, force[0], force[1], force[2], argument1);
