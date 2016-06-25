///MAE_PhysBodySetIgnore(body, other_body, ignore)

/**
 * Description:
 *   This function lets you tell 2 physics bodies to ignore collisions with each other.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Other body
 *   [2] - Ignore collisions with other body?
 *
 * Returns:
 *   Success
 */
 
return external_call(global.MAB_BodySetIgnore, argument0, argument1, argument2);
