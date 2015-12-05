///MAE_PhysBodyIsActive(body)

/**
 * Description:
 *   Checks if the body is active. (not sleeping)
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   1 if active, 0 otherwise.
 */

return external_call(global.MAB_BodyIsActive, argument0);
