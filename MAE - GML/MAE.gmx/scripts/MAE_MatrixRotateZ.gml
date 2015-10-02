///MAE_MatrixRotateZ(m, angle);

/**
 * To-do:
 *      Add Description.
 *
 */
return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationZ(MAE_MatrixGetDimension(argument0), argument1));
