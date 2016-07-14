///MAE_QuaternionMultiply(q1,q2);

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

var q;

q[3] = argument0[3] * argument1[3] - argument0[0] * argument1[0] - argument0[1] * argument1[1] - argument0[2] * argument1[2];
q[2] = argument0[3] * argument1[2] + argument0[2] * argument1[3] + argument0[0] * argument1[1] - argument0[1] * argument1[0];
q[1] = argument0[3] * argument1[1] + argument0[1] * argument1[3] + argument0[2] * argument1[0] - argument0[0] * argument1[2];
q[0] = argument0[3] * argument1[0] + argument0[0] * argument1[3] + argument0[1] * argument1[2] - argument0[2] * argument1[1];

return q;
