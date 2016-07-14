///MAE_PhysBodySetRotationQuat(body,rot);

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

var quat = argument1;

return external_call(global._MAB_BodySetRotationQuat, argument0, quat[0], quat[1], quat[2], quat[3]);
