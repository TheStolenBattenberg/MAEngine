///MAE_MatrixCreateRotationZ(dim,angle);

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

var c = dcos(argument1), s = dsin(argument1);

switch (argument0) {
case 2:
    var mat;
    
    mat[3] = c;
    mat[2] = s;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 3:
    var mat;
    
    mat[8] = 1;
    mat[7] = 0;
    mat[6] = 0;
    mat[5] = 0;
    mat[4] = c;
    mat[3] = s;
    mat[2] = 0;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 4:
    var mat;
    
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 0;
    mat[10] = 1;
    mat[09] = 0;
    mat[08] = 0;
    mat[07] = 0;
    mat[06] = 0;
    mat[05] = c;
    mat[04] = s;
    mat[03] = 0;
    mat[02] = 0;
    mat[01] = -s;
    mat[00] = c;
    
    return mat;
}

return undefined;
