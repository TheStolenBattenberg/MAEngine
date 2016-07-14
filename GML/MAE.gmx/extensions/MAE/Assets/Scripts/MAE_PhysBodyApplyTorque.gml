///MAE_PhysBodyApplyTorque(body,relative,torquex,torquey,torquez);

/**
 * Description:
 *   Applies torque to a physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Local space(true), or world space(false)
 *   [3] - Torque vector
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_BodyApplyTorque, argument0, argument2, argument3, argument4, argument1);
