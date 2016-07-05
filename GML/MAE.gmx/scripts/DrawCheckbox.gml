///DrawCheckbox(x, y, checkbox, label);

draw_set_colour(c_silver);
draw_rectangle(argument0, argument1, argument0+16, argument1+16, false);
draw_set_colour(c_gray);
draw_rectangle(argument0, argument1, argument0+16, argument1+16, true);

if(point_in_rectangle(mouse_x, mouse_y, argument0, argument1, argument0+16, argument1+16) && mouse_check_button_pressed(mb_left)) {
    chkbx[argument2, checkboxval.value] = !chkbx[argument2, checkboxval.value]; 
}

if(chkbx[argument2, checkboxval.value] == true) {
    draw_line(argument0+3, argument1+3, argument0+13, argument1+13);
    draw_line(argument0+13, argument1+3, argument0+3, argument1+13);
}

draw_set_halign(fa_right);
    draw_set_colour(c_white);
    draw_text(argument0-4, argument1, argument3+": ");
draw_set_halign(fa_left);

