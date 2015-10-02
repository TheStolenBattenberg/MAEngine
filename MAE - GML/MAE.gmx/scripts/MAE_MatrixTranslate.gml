///MAE_MatrixTranslate(m, v);

/**
 * To-do:
 *      Add Description.
 *
 */
var m14 = argument0[3];
var m24 = argument0[7];
var m34 = argument0[11];
var m44 = argument0[15];

// This if is only here to improve speed since m14, m24, m34 and m44 are often 0
// It can be commented out
if (m14 != 0 && m24 != 0 && m34 != 0) {
    argument0[00] += m14 * argument1[0];
    argument0[01] += m14 * argument1[1];
    argument0[02] += m14 * argument1[2];
    argument0[04] += m24 * argument1[0];
    argument0[05] += m24 * argument1[1];
    argument0[06] += m24 * argument1[2];
    argument0[08] += m34 * argument1[0];
    argument0[09] += m34 * argument1[1];
    argument0[10] += m34 * argument1[2];
}

argument0[12] += m44 * argument1[0];
argument0[13] += m44 * argument1[1];
argument0[14] += m44 * argument1[2];

return argument0;
