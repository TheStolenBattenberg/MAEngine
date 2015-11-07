///CreateFrameTab(string);
var strw = floor(string_width(argument0)/16);
var ds = ds_list_create();
ds_list_add(ds, -1);
ds_list_add(ds, argument0);
ds_list_add(ds, strw);
ds_list_add(ds, 64);
return ds;