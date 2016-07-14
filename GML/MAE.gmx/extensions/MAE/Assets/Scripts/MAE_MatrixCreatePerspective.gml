///MAE_MatrixCreatePerspective(fov,aspect,znear,zfar);

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

var yscale = 1 / dtan(argument0 / 2);
var xscale = yscale / argument1;

var mat;
{
    mat[15] = 0;
    mat[14] = -argument2 * argument3 / (argument3 - argument2);
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 1;
    mat[10] = argument3 / (argument3  - argument2);
    mat[9]  = 0;
    mat[8]  = 0;
    mat[7]  = 0;
    mat[6]  = 0;
    mat[5]  = yscale;
    mat[4]  = 0;
    mat[3]  = 0;
    mat[2]  = 0;
    mat[1]  = 0;
    mat[0]  = xscale;
}
return mat;
