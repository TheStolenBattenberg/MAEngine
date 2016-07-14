///MAE_PhysBodyApplyTorqueVector(body,relative,torque);

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

var torque = argument2;

return external_call(global._MAB_BodyApplyTorque, argument0, torque[0], torque[1], torque[2], argument1);
