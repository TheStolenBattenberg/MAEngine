///DrawWindow(x, y, width, height);
draw_set_colour(c_black);
draw_set_alpha(0.5);
draw_roundrect(argument0, argument1, argument0+argument2, argument1+argument3, false);
draw_set_colour(c_silver);
draw_set_alpha(1);
draw_roundrect(argument0, argument1, argument0+argument2, argument1+argument3, true);
