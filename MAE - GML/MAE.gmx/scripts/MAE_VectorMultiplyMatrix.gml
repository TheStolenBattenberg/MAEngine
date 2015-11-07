///MAE_VectorMultiplyMatrix(v, m);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument1)) {
case 4:
    if (array_length_1d(argument0) < 2)
        return undefined;
    
    var v;
    
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[3];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[2];
    
    return v;
case 9:
    if (array_length_1d(argument0) < 3)
        return undefined;
    
    var v;
    
    v[2] = argument0[0] * argument1[2] + argument0[1] * argument1[5] + argument0[2] * argument1[8];
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[4] + argument0[2] * argument1[7];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[3] + argument0[2] * argument1[6];
    
    return v;
case 16:
    if (array_length_1d(argument0) < 4) {
        if (array_length_1d(argument0) == 3)
            argument0[3] = 1;
        else
            return undefined;
    }
    
    var v;
    
    v[3] = argument0[0] * argument1[3] + argument0[1] * argument1[7] + argument0[2] * argument1[11] + argument0[3] * argument1[15];
    v[2] = argument0[0] * argument1[2] + argument0[1] * argument1[6] + argument0[2] * argument1[10] + argument0[3] * argument1[14];
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[5] + argument0[2] * argument1[9] + argument0[3] * argument1[13];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[4] + argument0[2] * argument1[8] + argument0[3] * argument1[12];
    
    return v;
}

return undefined;
