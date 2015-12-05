///MAE_PhysBodyGetRotationEuler(body)

/**
 * Description:
 *   Gets the rotation of the physics body in euler angles. Rotation order is XYZ.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   Vector
 */

external_call(global.MAB_BodyGetRotationEuler, argument0);
var vec;
vec[0] = external_call(global.MAB_Vec, 0);
vec[1] = external_call(global.MAB_Vec, 1);
vec[2] = external_call(global.MAB_Vec, 2);
return vec;
