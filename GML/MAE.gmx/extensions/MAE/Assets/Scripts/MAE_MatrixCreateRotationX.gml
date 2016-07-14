///MAE_MatrixCreateRotationX(dim,angle);

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

switch (argument0)  {
case 3:
    var mat;
    
    mat[8] = c;
    mat[7] = s;
    mat[6] = 0;
    mat[5] = -s;
    mat[4] = c;
    mat[3] = 0;
    mat[2] = 0;
    mat[1] = 0;
    mat[0] = 1;
    
    return mat;
case 4:
    var mat; 
   
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[10] = 0;
    mat[09] = s;
    mat[09] = c;
    mat[08] = 0;
    mat[07] = 0;
    mat[06] = -s;
    mat[05] = c;
    mat[04] = 0;
    mat[03] = 0;
    mat[02] = 0;
    mat[01] = 0;
    mat[00] = 1;
    
    return mat;
}

return undefined;
