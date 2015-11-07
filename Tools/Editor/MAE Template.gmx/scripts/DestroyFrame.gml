///DestroyFrame(Frame);
if(ds_exists(argument0, ds_type_list))
{
    if(surface_exists(argument0[| 0]))
    {
        surface_free(argument0[| 0])
    }
    ds_list_destroy(argument0);
    
    return 1;
}
return 0;
