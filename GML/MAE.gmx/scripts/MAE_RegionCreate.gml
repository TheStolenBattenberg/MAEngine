///MAE_RegionCreate(vec3 xyz, vec3 xyz, flags);

/**
 * To-do:
 *  Add description.
 */
 
ds = ds_list_create();
    ds[| 0] = argument0[0];
    ds[| 1] = argument0[1];
    ds[| 2] = argument0[2];
    ds[| 3] = argument1[0];
    ds[| 4] = argument1[1];
    ds[| 5] = argument1[2];
    ds[| 6] = ds_list_create();
    ds[| 7] = argument2;
return ds;
