///MAE_MatrixRotate(m,x,y,z,order = EULER_XYZ);

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

var _order = EULER_XYZ;

if (argument_count > 4)
    _order = argument[4];

return MAE_MatrixMultiplyMatrix(argument[0], MAE_MatrixCreateRotation(MAE_MatrixGetDimension(argument[0]), argument[1], argument[2], argument[3], _order));
