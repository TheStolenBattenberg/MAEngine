///MAE_QuaternionCreateRotationVector(v,angle);

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

var l = MAE_VectorMagnitude(argument0);

if (l == 0)
    return MAE_QuaternionCreateIdentity();

q[3] = dcos(argument1 / 2);
q[2] = argument0[2] / l * dsin(argument1 / 2);
q[1] = argument0[1] / l * dsin(argument1 / 2);
q[0] = argument0[0] / l * dsin(argument1 / 2);

return q;
