///MAE_PhysBodyApplyImpulseVector(body,position,impulse);

/**
 * Description:
 *   Applies an impulse to a physics body at the specified point in local space.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Position as a vector
 *   [3] - Force as a vector
 *
 * Returns:
 *   Success
 */

var position = argument1, impulse = argument2;

return external_call(global._MAB_BodyApplyImpulse, argument0, position[0], position[1], position[2], impulse[0], impulse[1], impulse[2]);
