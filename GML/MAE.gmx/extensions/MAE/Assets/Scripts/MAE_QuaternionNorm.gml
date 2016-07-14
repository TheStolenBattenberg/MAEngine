///MAE_QuaternionNorm(ref_q);

/**
 * Description:
 *   
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   [-]
 */

var l = MAE_QuaternionMagnitude(argument0);

if (l == 0)
    return undefined;

argument0[@ 0] /= l;
argument0[@ 1] /= l;
argument0[@ 2] /= l;
argument0[@ 3] /= l;

return argument0;
