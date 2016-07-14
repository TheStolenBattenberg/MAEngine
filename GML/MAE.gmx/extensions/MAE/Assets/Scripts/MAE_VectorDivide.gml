///MAE_VectorDivide(ref_v,quot);

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

switch (array_length_1d(argument0)) {
case 2:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    
    return argument0;
case 3:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    
    return argument0;
case 4:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    
    return argument0;
}

return undefined;
