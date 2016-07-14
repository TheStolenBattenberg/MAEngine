///MAE_MatrixRotateZ(m,angle);

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

return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationZ(MAE_MatrixGetDimension(argument0), argument1));
