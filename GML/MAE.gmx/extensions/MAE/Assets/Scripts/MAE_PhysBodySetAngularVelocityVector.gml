///MAE_PhysBodySetAngularVelocityVector(body,velocity);

/**
 * Description:
 *   Sets the angular velocity of the physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Velocity vector
 *
 * Returns:
 *   Success
 */

var velocity = argument1;

return external_call(global._MAB_BodySetAngularVelocity, argument0, velocity[0], velocity[1], velocity[2]);
