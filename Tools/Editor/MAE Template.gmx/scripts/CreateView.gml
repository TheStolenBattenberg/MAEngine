///CreateView(x, y, w, h, perspective);
if(instance_number(con_View) <= 3)
{
    var viewinst = instance_create(0, 0, con_View);
    viewinst.view_x = argument0;
    viewinst.view_y = argument1;
    viewinst.rt_w = argument2;
    viewinst.rt_h = argument3;
    viewinst.view_type = argument4;    
    viewinst.view_update = true;
    
    return viewinst;
}else{
    show_message("Only 4 or less views are allowed at one time.");
    return -1;
}
