///MAE_RegionUpdate(region);

/**
 * If you do this everystep, it's actually slower than 
 */
 
for(var reg = 0; reg < ds_list_size(argument0[| 6]); reg++)
{
    var obj = ds_list_find_value(argument0[| 6], reg);
    with(obj) {
        event_perform(ev_draw, 0);
    }
}
return true;
