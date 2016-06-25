///MAE_PhysBodyIsDynamic(body)

/**
 * Description:
 *   Checks if the body is dynamic.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   1 if dynamic, 0 otherwise.
 */

return !(MAE_PhysBodyIsStatic(argument0) || MAE_PhysBodyIsKinematic(argument0));
