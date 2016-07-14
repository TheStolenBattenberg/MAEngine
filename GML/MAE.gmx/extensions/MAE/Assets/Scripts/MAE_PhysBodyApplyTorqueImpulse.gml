///MAE_PhysBodyApplyTorqueImpulse(body,relative,impx,impy,impz);

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

return external_call(global._MAB_BodyApplyTorqueImpulse, argument0, argument2, argument3, argument4, argument1);
