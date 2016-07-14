///MAE_MatrixTranslate(m,v);

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

var m14 = argument0[3];
var m24 = argument0[7];
var m34 = argument0[11];
var m44 = argument0[15];

if (sign(m14) != 0 || sign(m24) != 0 || sign(m34) != 0) {
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
