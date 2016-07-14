///MAE_MatrixGetDimension(m);

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

switch (array_length_1d(argument0)) {
case 4:
    return 2;
case 9:
    return 3;
case 16:
    return 4;
}

return undefined;
