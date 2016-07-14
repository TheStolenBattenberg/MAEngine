///MAE_PhysBodyApplyCentralImpulse(body,relative,impulse);

/**
 * Description:
 *   Applies an impulse to the center of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Local space(true), or world space(false)
 *   [3] - Impulse as a vector
 *
 * Returns:
 *   Success
 */

var impulse = argument2;

return external_call(global._MAB_BodyApplyCentralImpulse, argument0, impulse[0], impulse[1], impulse[2], argument1);
