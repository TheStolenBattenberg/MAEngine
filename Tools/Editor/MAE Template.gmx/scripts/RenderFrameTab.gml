///RenderFrameTab(frametab, x, y);

if(!surface_exists(argument0[| 0]))
{
    //show_debug_message("Possible Warning: Re-Creating Widget: "+string(argument0));
    argument0[| 0] = surface_create(32 + (16 * argument0[| 2]), argument0[| 3]);

    surface_set_target(argument0[| 0]);
    {
        draw_sprite(global.THEME[settheme, themes.FrameTab], 0, 0, 0);
        for(var i = 0; i < argument0[| 2]; i++)
        {
            draw_sprite(global.THEME[settheme, themes.FrameTab], 1, 16 + (16*i), 0);
        }

        draw_sprite(global.THEME[settheme, themes.FrameTab], 2, 16 + (16*i), 0);

        var strx = ((32 + (16*i))/2) - (string_width(argument0[| 1])/2);
        var strc = global.THEME[settheme, themes.HeadingColour];
        draw_text_colour(strx, 8, argument0[| 1], strc, strc, strc, strc, 1);
    }
    surface_reset_target();
}
draw_surface(argument0[| 0], argument1, argument2);
return (16*(argument0[| 2]+1)+16);
