///MAE_PhysBodySetLinearVelocityVector(body,velocity);

/**
 * Description:
 *   Sets the linear velocity of the physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Velocity vector
 *
 * Returns:
 *   Success
 */

var velocity = argument1;

return external_call(global._MAB_BodySetLinearVelocity, argument0, velocity[0], velocity[1], velocity[2]);
