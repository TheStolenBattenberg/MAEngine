///MAE_PhysWorldGetGravity();

/**
 * Description:
 *   Gets the gravity of the physics world.
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   Vector
 */

external_call(global._MAB_WorldGetGravity);

return MAE_VectorCreate(external_call(global._MAB_Vec, 0),
                        external_call(global._MAB_Vec, 1),
                        external_call(global._MAB_Vec, 2));
