///MAE_PhysBodyGetTransform(body)

/**
 * Description:
 *   Gets the transformation of a physics body as a matrix. This matrix holds both the position and rotation.
 *   This is the easiest way to get the transformation of a body for rendering.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   4x4 Matrix
 */

var _pos = MAE_PhysBodyGetPosition(argument0);
var _rot = MAE_PhysBodyGetRotationQuat(argument0);
var _mat_r = MAE_MatrixCreateRotationQuaternion(4, _rot);
var _mat_p = MAE_MatrixCreateTranslation(_pos);
return MAE_MatrixMultiplyMatrix(_mat_r, _mat_p);
