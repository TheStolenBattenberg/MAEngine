///MAE_PhysBodySetRotation(body,x,y,z);

/**
 * Description:
 *   Sets the rotation of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Rotation. Can be a vector of euler angles or a quaternion.
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_BodySetRotationEuler, argument0, argument1, argument2, argument3);
