///MAE_MatrixRotateQuaternion(m,q);

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

return MAE_MatrixMultiplyMatrix(argument0, MAE_MatrixCreateRotationQuaternion(MAE_MatrixGetDimension(argument0), argument1));
