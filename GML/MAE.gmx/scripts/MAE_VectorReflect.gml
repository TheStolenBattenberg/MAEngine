///MAE_VectorReflect(v, n);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 2:
    var dot2 = 2 * (argument0[0] * argument1[0] + argument0[1] * argument1[1]);
    
    var v;
    
    v[1] = argument1[1] * dot2 - argument0[1];
    v[0] = argument1[0] * dot2 - argument0[0];
    
    return v;
case 3:
    var dot2 = 2 * (argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2]);
    
    var v;
    
    v[2] = argument1[2] * dot2 - argument0[2];
    v[1] = argument1[1] * dot2 - argument0[1];
    v[0] = argument1[0] * dot2 - argument0[0];
    
    return v;
}

return undefined;
