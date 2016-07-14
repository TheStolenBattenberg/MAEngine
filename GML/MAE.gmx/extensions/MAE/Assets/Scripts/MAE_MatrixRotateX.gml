///MAE_MatrixRotateX(m,angle);

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

return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationX(MAE_MatrixGetDimension(argument0), argument1));
