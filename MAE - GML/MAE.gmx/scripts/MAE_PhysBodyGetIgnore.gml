///MAE_PhysBodyGetIgnore(body, other_body)

/**
 * Description:
 *   Checks if this body is ignoring collisions with the other one.
 *   See MAE_PhysBodySetIgnore() to make a body ignore another.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Other body.
 *
 * Returns:
 *   1 if ignoring, 0 otherwise.
 */

return external_call(global.MAB_BodyGetIgnore, argument0, argument1);
