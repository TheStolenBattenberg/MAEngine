///MAE_PhysBodyIsKinematic(body)

/**
 * Description:
 *   Checks if the body is kinematic.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   1 if kinematic, 0 otherwise.
 */

return external_call(global.MAB_BodyIsKinematic, argument0);
