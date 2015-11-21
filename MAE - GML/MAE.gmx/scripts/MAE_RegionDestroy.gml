///MAE_RegionDestroy(region, destroyinstances);

/**
 *
 */
if(argument1 == true)
{
    for(var reg = 0; reg < ds_list_size(argument0[| 6]); i++)
    {
        with(ds_list_find_value(argument0[| 6], i))
        {
            instance_destroy();
        }
    }
    
    ds_list_clear(argument0[| 6]);
    ds_list_destroy(argument0[| 6]);
}else{
    ds_list_clear(argument0[| 6]);
    ds_list_destroy(argument0[| 6]);
}
