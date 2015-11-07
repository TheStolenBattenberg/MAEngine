///UpdateViews();

var vsh = 0;
var vsw = 0;
for(i = 0; i < view_count; i++)
{
    Views[i].view_x = 352 + ((view_area_w/2) * vsw);
    Views[i].view_y = 24 + ((view_area_h/2) * floor(vsh));
    
    
    vsh+=0.51;
    vsw++;
    if(floor(vsh) == 1 && vsw > 1)
    {
        vsw = 0;
    }
    Views[i].view_update = true;
}
