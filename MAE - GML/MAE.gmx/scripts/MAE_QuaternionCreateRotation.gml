///MAE_QuaternionCreateRotation(x, y, z);

/**
 * To-do:
 *      Add Description.
 *
 */
var sx = dsin(argument0 / 2);
var cx = dcos(argument0 / 2);
var sy = dsin(argument1 / 2);
var dy = dcos(argument1 / 2);
var sz = dsin(argument2 / 2);
var cz = dcos(argument2 / 2);

var ret;

ret[3] = cx * dy * cz + sx * sy * sz;
ret[2] = cx * dy * sz - sx * sy * cz;
ret[1] = cx * sy * cz + sx * dy * sz;
ret[0] = sx * dy * cz - cx * sy * sz;

return ret;
