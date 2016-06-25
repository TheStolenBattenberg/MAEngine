///MAE_QuaternionCreateRotation(x, y, z, [order]);

/**
 * To-do:
 *      Add Description.
 *
 */
var order = EULER_XYZ;

if (argument_count > 3)
    order = argument[3];

var sx = dsin(argument[0] / 2);
var cx = dcos(argument[0] / 2);
var sy = dsin(argument[1] / 2);
var cy = dcos(argument[1] / 2);
var sz = dsin(argument[2] / 2);
var cz = dcos(argument[2] / 2);

var ret;

switch (order) {
case EULER_XYZ:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_YXZ:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_ZXY:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
case EULER_ZYX:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
case EULER_YZX:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_XZY:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
default:
    return undefined;
}

return ret;
