///MAE_MatrixRotateY(m,angle);

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

return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationY(MAE_MatrixGetDimension(argument0), argument1));
