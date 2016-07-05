///DrawSlider(x, y, width, slider, label);

draw_set_colour(c_black);
draw_line_width(argument0, argument1, argument0+argument2, argument1, 2);

var positn = (argument2/sldr[argument3, sliderval.mmax])*sldr[argument3, sliderval.value];

if(point_in_circle(mouse_x, mouse_y, argument0+positn, argument1, 4) & mouse_check_button(mb_left)) {
    vl = (mouse_x-argument0);
    sldr[argument3, sliderval.value] = vl/(sldr[argument3, sliderval.mmax]/2);
}

draw_set_colour(c_silver);
draw_circle(argument0+positn, argument1, 4, false);
draw_set_colour(c_gray);
draw_circle(argument0+positn, argument1, 4, true);

draw_set_halign(fa_center);
    draw_set_colour(c_white);
    draw_text(argument0+(argument2/2), argument1-20, argument4+": "+string(sldr[argument3, sliderval.value]));
draw_set_halign(fa_left);
