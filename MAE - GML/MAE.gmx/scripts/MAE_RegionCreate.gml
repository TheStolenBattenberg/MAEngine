///MAE_CreateRegion(vec3 xyz, vec3 xyz, flags);

/**
 * To-do:
 *  Add description.
 */
 
ds = ds_list_create();
    ds[| 0] = argument0[0]; //x
    ds[| 1] = argument0[1]; //y
    ds[| 2] = argument0[2]; //z
    ds[| 3] = argument1[0]; //x2
    ds[| 4] = argument1[1]; //y2
    ds[| 5] = argument1[2]; //z2
    ds[| 6] = ds_list_create();
    ds[| 7] = argument2;
return ds;
