//MAE_PhysWorldHitNormal()

/**
 * Description:
 *   Returns the surface normal at the hit point of a sweep or raycast.
 *
 * Arguments:
 *   [N/A]
 *
 * Returns:
 *   Vector
 */

external_call(global.MAB_HitResult, 1);
var vec;
vec[0] = external_call(global.MAB_Vec, 0);
vec[1] = external_call(global.MAB_Vec, 1);
vec[2] = external_call(global.MAB_Vec, 2);
return vec;
