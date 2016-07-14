///MAE_PhysBodyIsActive(body);

/**
 * Description:
 *   Checks if the body is active. (not sleeping)
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   1 if active, 0 otherwise.
 */

return external_call(global._MAB_BodyIsActive, argument0);
