//MAE_PhysWorldHitPosition()

/**
 * Description:
 *   Returns the hit point of a sweep or raycast.
 *
 * Arguments:
 *   [N/A]
 *
 * Returns:
 *   Vector
 */

external_call(global.MAB_HitResult, 0);
var vec;
vec[0] = external_call(global.MAB_Vec, 0);
vec[1] = external_call(global.MAB_Vec, 1);
vec[2] = external_call(global.MAB_Vec, 2);
return vec;
