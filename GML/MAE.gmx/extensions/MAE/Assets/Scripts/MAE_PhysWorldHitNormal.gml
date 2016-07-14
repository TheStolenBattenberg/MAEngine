///MAE_PhysWorldHitNormal();

/**
 * Description:
 *   Returns the surface normal at the hit point of a sweep or raycast.
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   Vector
 */

external_call(global._MAB_HitResult, 1);

return MAE_VectorCreate(external_call(global._MAB_Vec, 0),
                        external_call(global._MAB_Vec, 1),
                        external_call(global._MAB_Vec, 2));
