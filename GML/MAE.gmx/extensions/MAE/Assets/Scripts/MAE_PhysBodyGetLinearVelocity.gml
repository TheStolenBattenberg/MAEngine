///MAE_PhysBodyGetLinearVelocity(body);

/**
 * Description:
 *   Gets the linear velocity of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Vector
 */

external_call(global._MAB_BodyGetLinearVelocity, argument0);

return MAE_VectorCreate(external_call(global._MAB_Vec, 0),
                        external_call(global._MAB_Vec, 1),
                        external_call(global._MAB_Vec, 2));
