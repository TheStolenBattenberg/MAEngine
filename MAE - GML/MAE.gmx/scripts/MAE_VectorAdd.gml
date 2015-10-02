///MAE_VectorAdd(v1, v2);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 2:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    
    return argument0;
case 3:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    argument0[2] += argument1[2];
    
    return argument0;
case 4:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    argument0[2] += argument1[2];
    argument0[3] += argument1[3];
    
    return argument0;
}

return undefined;
