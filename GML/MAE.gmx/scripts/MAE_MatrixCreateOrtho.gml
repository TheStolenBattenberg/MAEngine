///MAE_MatrixCreateOrtho(x1, y1, x2, y2, znear, zfar);

/**
 * To-do:
 *      Add Description.
 *
 */
var mat;
{
    mat[15] = 1;
    mat[14] = argument4 / (argument4 - argument5);
    mat[13] = (argument1 + argument3) / (argument3 - argument1);
    mat[12] = (argument0 + argument2) / (argument0 - argument2);
    mat[11] = 0;
    mat[10] = 1 / (argument5 - argument4);
    mat[9]  = 0;
    mat[8]  = 0;
    mat[7]  = 0;
    mat[6]  = 0;
    mat[5]  = 2 / (argument1 - argument3);
    mat[4]  = 0;
    mat[3]  = 0;
    mat[2]  = 0;
    mat[1]  = 0;
    mat[0]  = 2 / (argument2 - argument0);
}
return mat;
