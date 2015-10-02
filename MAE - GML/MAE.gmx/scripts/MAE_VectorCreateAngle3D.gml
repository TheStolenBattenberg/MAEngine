///MAE_VectorCreateAngle3D(yaw, pitch);

/**
 * To-do:
 *      Add Description.
 *
 */
var v;

v[2] = dsin(argument1);
v[1] = -dsin(argument0) * dcos(argument1);
v[0] = dcos(argument0) * dcos(argument1);

return v;
