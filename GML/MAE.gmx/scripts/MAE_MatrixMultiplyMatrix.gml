///MAE_MatrixMultiplyMatrix(m1, m2);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    var mat;
    
    mat[3] = argument0[2] * argument1[1] + argument0[3] * argument1[3];
    mat[2] = argument0[2] * argument1[0] + argument0[3] * argument1[2];
    mat[1] = argument0[0] * argument1[1] + argument0[1] * argument1[3];
    mat[0] = argument0[0] * argument1[0] + argument0[1] * argument1[2];
    
    return mat;
case 9:
    var mat;
    
    mat[8] = argument0[6] * argument1[2] + argument0[7] * argument1[5] + argument0[8] * argument1[8];
    mat[7] = argument0[6] * argument1[1] + argument0[7] * argument1[4] + argument0[8] * argument1[7];
    mat[6] = argument0[6] * argument1[0] + argument0[7] * argument1[3] + argument0[8] * argument1[6];
    mat[5] = argument0[3] * argument1[2] + argument0[4] * argument1[5] + argument0[5] * argument1[8];
    mat[4] = argument0[3] * argument1[1] + argument0[4] * argument1[4] + argument0[5] * argument1[7];
    mat[3] = argument0[3] * argument1[0] + argument0[4] * argument1[3] + argument0[5] * argument1[6];
    mat[2] = argument0[0] * argument1[2] + argument0[1] * argument1[5] + argument0[2] * argument1[8];
    mat[1] = argument0[0] * argument1[1] + argument0[1] * argument1[4] + argument0[2] * argument1[7];
    mat[0] = argument0[0] * argument1[0] + argument0[1] * argument1[3] + argument0[2] * argument1[6];
    
    return mat;
case 16:
    return matrix_multiply(argument0, argument1);
}

return undefined;
