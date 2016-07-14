///MAE_VectorDot(v1,v2);

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
    return argument0[0] * argument1[0] + argument0[1] * argument1[1];
case 3:
    return argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2];
case 4:
    return argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2] + argument0[3] * argument1[3];
}

return undefined;
