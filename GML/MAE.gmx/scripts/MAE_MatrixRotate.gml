///MAE_MatrixRotate(m, x, y, z, [order]);

/**
 * To-do:
 *      Add Description.
 *
 */
var order = EULER_XYZ;

if (argument_count > 4)
    order = argument[4];

return MAE_MatrixMultiplyMatrix(argument[0], MAE_MatrixCreateRotation(MAE_MatrixGetDimension(argument0), argument[1], argument[2], argument[3], order));
