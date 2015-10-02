///MAE_MatrixToMat3(m);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    var m;
    
    m[8] = 1;
    m[7] = 0;
    m[6] = 0;
    m[5] = 0;
    m[4] = argument0[3];
    m[3] = argument0[2];
    m[2] = 0;
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
case 9:
    argument0[0] = argument0[0];
    
    return argument0;
case 16:
    var m;
    
    m[8] = argument0[10];
    m[7] = argument0[9];
    m[6] = argument0[8];
    m[5] = argument0[6];
    m[4] = argument0[5];
    m[3] = argument0[4];
    m[2] = argument0[2];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
}

return undefined;
