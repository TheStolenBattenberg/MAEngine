///MAE_VectorMagnitude(v);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 2:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1]);
case 3:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2]);
case 4:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2] + argument0[3] * argument0[3]);
}

return undefined;
