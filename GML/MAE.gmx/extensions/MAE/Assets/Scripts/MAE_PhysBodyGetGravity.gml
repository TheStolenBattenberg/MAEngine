///MAE_PhysBodyGetGravity(body);

/**
 * Description:
 *   Gets the gravity force of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Vector
 */

external_call(global._MAB_BodyGetGravity, argument0);

return MAE_VectorCreate(external_call(global._MAB_Vec, 0),
                        external_call(global._MAB_Vec, 1),
                        external_call(global._MAB_Vec, 2));
