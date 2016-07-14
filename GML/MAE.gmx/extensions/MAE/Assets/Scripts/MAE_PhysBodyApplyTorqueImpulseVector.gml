///MAE_PhysBodyApplyTorqueImpulseVector(body,relative,impulse);

/**
 * Description:
 *   Applies torque impulse to a physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Local space(true), or world space(false)
 *   [3] - Torque vector
 *
 * Returns:
 *   Success
 */

var impulse = argument2;

return external_call(global._MAB_BodyApplyTorqueImpulse, argument0, impulse[0], impulse[1], impulse[2], argument1);
