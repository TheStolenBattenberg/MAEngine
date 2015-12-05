///MAE_PhysBodySetDamping(body, linear_damping, angular_damping)

/**
 * Description:
 *   Sets the damping of a physics body.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Linear damping
 *   [2] - Angular damping
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_BodySetDamping, argument0, argument1, argument2);
