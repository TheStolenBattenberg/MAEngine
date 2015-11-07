///MAE_MatrixCreateRotationY(dim, angle);

/**
 * To-do:
 *      Add Description.
 *
 */
var c = dcos(argument1), s = dsin(argument1);

switch (argument0) {
case 3:
    var mat;
    
    mat[8] = c;
    mat[7] = 0;
    mat[6] = -s;
    mat[5] = 0;
    mat[4] = 1;
    mat[3] = 0;
    mat[2] = s;
    mat[1] = 0;
    mat[0] = c;
    
    return mat;
case 4:
    var mat;
    
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 0;
    mat[10] = c;
    mat[09] = 0;
    mat[08] = -s;
    mat[07] = 0;
    mat[06] = 0;
    mat[05] = 1;
    mat[04] = 0;
    mat[03] = 0;
    mat[02] = s;
    mat[01] = 0;
    mat[00] = c;
    
    return mat;
}

return undefined;
