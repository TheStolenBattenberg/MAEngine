///MAE_MatrixToMat2(m);

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
case 4:
    argument0[0] = argument0[0];
    
    return argument0;
case 9:
    var m;
    
    m[3] = argument0[4];
    m[2] = argument0[3];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
case 16:
    var m;
    
    m[3] = argument0[5];
    m[2] = argument0[4];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
}

return undefined;
