///MAE_MatrixCreateRotationY(dim, angle);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (argument0) {
case 3:
    var mat;
    
    mat[8] = dcos(argument1);
    mat[7] = 0;
    mat[6] = dsin(argument1);
    mat[5] = 0;
    mat[4] = 1;
    mat[3] = 0;
    mat[2] = -dsin(argument1);
    mat[1] = 0;
    mat[0] = dcos(argument1);
    
    return mat;
case 4:
    var mat;
    
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 0;
    mat[10] = dcos(argument1);
    mat[09] = 0;
    mat[08] = dsin(argument1);
    mat[07] = 0;
    mat[06] = 0;
    mat[05] = 1;
    mat[04] = 0;
    mat[03] = 0;
    mat[02] = -dsin(argument1);
    mat[01] = 0;
    mat[00] = dcos(argument1);
    
    return mat;
}

return undefined;
