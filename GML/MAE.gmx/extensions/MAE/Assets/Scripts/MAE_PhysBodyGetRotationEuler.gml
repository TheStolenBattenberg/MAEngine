///MAE_PhysBodyGetRotationEuler(body);

/**
 * Description:
 *   Gets the rotation of the physics body in euler angles. Rotation order is XYZ.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Vector
 */

external_call(global._MAB_BodyGetRotationEuler, argument0);

return MAE_VectorCreate(external_call(global._MAB_Vec, 0),
                        external_call(global._MAB_Vec, 1),
                        external_call(global._MAB_Vec, 2));
