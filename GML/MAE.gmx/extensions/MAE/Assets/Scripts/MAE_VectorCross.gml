///MAE_VectorCross(v1,v2);

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

var v;

v[2] = argument0[0] * argument1[1] - argument0[1] * argument1[0];
v[1] = argument0[2] * argument1[0] - argument0[0] * argument1[2];
v[0] = argument0[1] * argument1[2] - argument0[2] * argument1[1];

return v;
