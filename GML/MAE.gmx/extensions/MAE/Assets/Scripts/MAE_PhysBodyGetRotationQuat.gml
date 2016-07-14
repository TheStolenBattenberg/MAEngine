///MAE_PhysBodyGetRotationQuat(body);

/**
 * Description:
 *   Gets the rotation of the physics body as a quaternion.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Quaternion.
 */

external_call(global._MAB_BodyGetRotationQuat, argument0);

return MAE_QuaternionCreate(external_call(global._MAB_Quat, 0),
                            external_call(global._MAB_Quat, 1),
                            external_call(global._MAB_Quat, 2),
                            external_call(global._MAB_Quat, 3));
