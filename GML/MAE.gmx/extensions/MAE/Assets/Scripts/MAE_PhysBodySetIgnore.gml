///MAE_PhysBodySetIgnore(body,other_body,ignore);

/**
 * Description:
 *   This function lets you tell 2 physics bodies to ignore collisions with each other.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Other body
 *   [3] - Ignore collisions with other body?
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_BodySetIgnore, argument0, argument1, argument2);
