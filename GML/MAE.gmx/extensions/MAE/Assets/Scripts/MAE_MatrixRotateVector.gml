///MAE_MatrixRotateVector(m,v,angle);

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

return MAE_MatrixMultiplyMatrix(argument0, MAE_MatrixCreateRotationVector(MAE_MatrixGetDimension(argument0), argument1, argument2));
