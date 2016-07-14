///MAE_PhysBodySetPositionVector(body,pos);

/**
 * Description:
 *   Sets the position of the physics body in the world.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Position as a vector
 *
 * Returns:
 *   Success
 */

var pos = argument1;

return external_call(global._MAB_BodySetPosition, argument0, pos[0], pos[1], pos[2]);
