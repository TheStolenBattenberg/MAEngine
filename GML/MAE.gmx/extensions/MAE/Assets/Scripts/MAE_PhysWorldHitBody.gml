///MAE_PhysWorldHitBody(n = -1);

/**
 * Description:
 *   Returns the id of the hit body of a collision check. 
 *
 * Arguments:
 *   [1] - Optional. Only for overlap checks, returns body n that was overlapped.
 *
 * Returns:
 *   Body ID
 */

var _n = -1;

if (argument_count > 0)
    _n = argument[0];

if(_n < 0)
    return external_call(global._MAB_HitResult, 3);

return external_call(global._MAB_OverlapResult, _n);
