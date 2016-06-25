///MAE_MatrixDivide(ref_m, quot);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    
    return argument0;
case 9:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    argument0[@ 4] /= argument1;
    argument0[@ 5] /= argument1;
    argument0[@ 6] /= argument1;
    argument0[@ 7] /= argument1;
    argument0[@ 8] /= argument1;
    
    return argument0;
case 16:
    argument0[@ 00] /= argument1;
    argument0[@ 01] /= argument1;
    argument0[@ 02] /= argument1;
    argument0[@ 03] /= argument1;
    argument0[@ 04] /= argument1;
    argument0[@ 05] /= argument1;
    argument0[@ 06] /= argument1;
    argument0[@ 07] /= argument1;
    argument0[@ 08] /= argument1;
    argument0[@ 09] /= argument1;
    argument0[@ 10] /= argument1;
    argument0[@ 11] /= argument1;
    argument0[@ 12] /= argument1;
    argument0[@ 13] /= argument1;
    argument0[@ 14] /= argument1;
    argument0[@ 15] /= argument1;
    
    return argument0;
}

return undefined;
