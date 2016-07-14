///MAE_PhysBodySetRotationVec(body,rot);

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

var vec = argument1;

return external_call(global._MAB_BodySetRotationEuler, argument0, vec[0], vec[1], vec[2]);
