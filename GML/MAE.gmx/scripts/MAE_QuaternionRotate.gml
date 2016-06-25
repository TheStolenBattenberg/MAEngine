///MAE_QuaternionRotate(q, x, y, z, [order]);

/**
 * To-do:
 *      Add Description.
 *
 */
var order = EULER_XYZ;

if (argument_count > 4)
    order = argument[4];

return MAE_QuaternionMultiply(argument0, MAE_QuaternionCreateRotation(argument1, argument2, argument3, order));
