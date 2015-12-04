//MAE_PhysWorldHitBody([n])

/**
 * Description:
 *   Returns the id of the hit body of a collision check. 
 *
 * Arguments:
 *   [0] - Optional. Only for overlap checks, returns body n that was overlapped.
 *
 * Returns:
 *   Body ID
 */

if(argument_count == 0) return external_call(global.MAB_HitResult, 3);
else return external_call(global.MAB_OverlapResult, argument[0]);
