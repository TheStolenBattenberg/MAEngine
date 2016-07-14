///MAE_PhysBodySetGravityVector(body,gravity);

/**
 * Description:
 *   Overrides the world gravity on a body with a different gravity force.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Success
 */

var vec = argument1;

return external_call(global._MAB_BodySetGravity, argument0, vec[0], vec[1], vec[2]);
