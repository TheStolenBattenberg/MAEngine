///MAE_PhysBodyGetRotationMatrix(body)

/**
 * Description:
 *   Gets the rotation of a physics body as a matrix.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   4x4 Matrix
 */

var _rot = MAE_PhysBodyGetRotationQuat(argument0);
return MAE_MatrixCreateRotationQuaternion(4, _rot);
