///MAE_PhysBodyDisableDeactivation(body)

/**
 * Description:
 *   Disables sleeping for a body. If you call this, the body will never sleep.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_BodySetDeactivationTime, argument0);
