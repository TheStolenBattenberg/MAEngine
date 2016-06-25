///MAE_MatrixInverse(m);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    var mat;
    
    mat[3] =  argument0[0];
    mat[2] = -argument0[2];
    mat[1] = -argument0[1];
    mat[0] =  argument0[3];
    
    var det = argument0[0] * argument0[3] - argument0[2] * argument0[1];
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
case 9:
    var mat;
    
    mat[8] = argument0[4] * argument0[0] - argument0[3] * argument0[1];
    mat[7] = argument0[1] * argument0[6] - argument0[0] * argument0[7];
    mat[6] = argument0[3] * argument0[7] - argument0[6] * argument0[4];
    mat[5] = argument0[3] * argument0[2] - argument0[5] * argument0[0];
    mat[4] = argument0[0] * argument0[8] - argument0[2] * argument0[6];
    mat[3] = argument0[5] * argument0[6] - argument0[8] * argument0[3];
    mat[2] = argument0[5] * argument0[1] - argument0[4] * argument0[2];
    mat[1] = argument0[2] * argument0[7] - argument0[1] * argument0[8];
    mat[0] = argument0[4] * argument0[8] - argument0[7] * argument0[5];
    
    var det = argument0[0] * (argument0[4] * argument0[8] - argument0[7] * argument0[5]) -
              argument0[3] * (argument0[1] * argument0[8] - argument0[7] * argument0[2]) +
              argument0[6] * (argument0[1] * argument0[5] - argument0[4] * argument0[2])
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
case 16:
    var val00 = argument0[10] * argument0[15] - argument0[14] * argument0[11];
    var val01 = argument0[09] * argument0[15] - argument0[13] * argument0[11];
    var val02 = argument0[09] * argument0[14] - argument0[13] * argument0[10];
    var val03 = argument0[08] * argument0[15] - argument0[12] * argument0[11];
    var val04 = argument0[08] * argument0[14] - argument0[12] * argument0[10];
    var val05 = argument0[08] * argument0[13] - argument0[12] * argument0[09];
    var val06 = argument0[06] * argument0[15] - argument0[14] * argument0[07];
    var val07 = argument0[05] * argument0[15] - argument0[13] * argument0[07];
    var val08 = argument0[05] * argument0[14] - argument0[13] * argument0[06];
    var val09 = argument0[04] * argument0[15] - argument0[12] * argument0[07];
    var val10 = argument0[04] * argument0[14] - argument0[12] * argument0[06];
    var val11 = argument0[05] * argument0[15] - argument0[13] * argument0[07];
    var val12 = argument0[04] * argument0[13] - argument0[12] * argument0[05];
    var val13 = argument0[06] * argument0[11] - argument0[10] * argument0[07];
    var val14 = argument0[05] * argument0[11] - argument0[09] * argument0[07];
    var val15 = argument0[05] * argument0[10] - argument0[09] * argument0[06];
    var val16 = argument0[04] * argument0[11] - argument0[08] * argument0[07];
    var val17 = argument0[04] * argument0[10] - argument0[08] * argument0[06];
    var val18 = argument0[04] * argument0[09] - argument0[08] * argument0[05];
    
    var mat;
    
    mat[15] =  argument0[0] * val15 - argument0[1] * val17 + argument0[2] * val18;
    mat[14] = -argument0[0] * val08 + argument0[1] * val10 - argument0[2] * val12;
    mat[13] =  argument0[0] * val02 - argument0[1] * val04 + argument0[2] * val05;
    mat[12] = -argument0[4] * val02 + argument0[5] * val04 - argument0[6] * val05;
    mat[11] = -argument0[0] * val14 + argument0[1] * val16 - argument0[3] * val18;
    mat[10] =  argument0[0] * val11 - argument0[1] * val09 + argument0[3] * val12;
    mat[09] = -argument0[0] * val01 + argument0[1] * val03 - argument0[3] * val05;
    mat[08] =  argument0[4] * val01 - argument0[5] * val03 + argument0[7] * val05;
    mat[07] =  argument0[0] * val13 - argument0[2] * val16 + argument0[3] * val17;
    mat[06] = -argument0[0] * val06 + argument0[2] * val09 - argument0[3] * val10;
    mat[05] =  argument0[0] * val00 - argument0[2] * val03 + argument0[3] * val04;
    mat[04] = -argument0[4] * val00 + argument0[6] * val03 - argument0[7] * val04;
    mat[03] = -argument0[1] * val13 + argument0[2] * val14 - argument0[3] * val15;
    mat[02] =  argument0[1] * val06 - argument0[2] * val07 + argument0[3] * val08;
    mat[01] = -argument0[1] * val00 + argument0[2] * val01 - argument0[3] * val02;
    mat[00] =  argument0[5] * val00 - argument0[6] * val01 + argument0[7] * val02;
    
    var det = argument0[0] * mat[0] + argument0[1] * mat[4] + argument0[2] * mat[8] + argument0[3] * mat[12];
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
}

return undefined;
