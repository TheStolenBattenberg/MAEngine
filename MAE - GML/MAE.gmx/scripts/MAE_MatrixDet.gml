///MAE_MatrixDet(m);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    return argument0[0] * argument[3] - argument0[2] * argument0[1];
case 9:
    return argument0[0] * argument0[4] * argument0[8] + argument0[3] * argument0[7] * argument0[2] +
           argument0[6] * argument0[1] * argument0[5] - argument0[6] * argument0[4] * argument0[2] -
           argument0[3] * argument0[1] * argument0[8] - argument0[0] * argument0[7] * argument0[5];
case 16:
    return argument0[00] * argument0[05] * argument0[10] * argument0[15] + argument0[04] * argument0[09] * argument0[14] * argument0[03] +
           argument0[08] * argument0[13] * argument0[02] * argument0[07] + argument0[12] * argument0[01] * argument0[06] * argument0[11] -
           argument0[12] * argument0[09] * argument0[06] * argument0[03] - argument0[08] * argument0[05] * argument0[02] * argument0[15] -
           argument0[04] * argument0[01] * argument0[14] * argument0[11] - argument0[00] * argument0[13] * argument0[10] * argument0[07];
}

return undefined;
