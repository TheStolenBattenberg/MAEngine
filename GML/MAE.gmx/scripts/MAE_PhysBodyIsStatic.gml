///MAE_PhysBodyIsStatic(body)

/**
 * Description:
 *   Checks if the body is static.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   1 if static, 0 otherwise.
 */

return external_call(global.MAB_BodyIsStatic, argument0);
