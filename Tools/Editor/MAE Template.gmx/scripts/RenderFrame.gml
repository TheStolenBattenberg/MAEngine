///RenderFrame(frame, x, y);
if(!surface_exists(argument0[| 0]))
{
    //show_debug_message("Possible Warning: Re-Creating Widget: "+string(argument0));
    argument0[| 0] = surface_create(argument0[| 1], argument0[| 2]);
    
    surface_set_target(argument0[| 0]);
    {
        var framebc1 = global.THEME[settheme, themes.HighlightColour1];
        var framebc2 = global.THEME[settheme, themes.HighlightColour2];
        var framec = global.THEME[settheme, themes.BodyColour];
        
        /**
         * Had there's weird offset and errors with the drawing scripts... Had to draw borders with lines due to the corners missing.
         *
         * It's probably going to need updating in the future because of this.
         */
        draw_rectangle_colour(0, 0, argument0[| 1]-1, argument0[| 2]-1, framec, framec, framec, framec, false);
        { //Border 1
            draw_line_colour(-1, 0, argument0[| 1]-1, 0, framebc1, framebc1); //Top
            draw_line_colour(-1, argument0[| 2]-1, argument0[| 1]-1, argument0[| 2]-1, framebc1, framebc1); //Bottom
            draw_line_colour(-1, 0, 0, argument0[| 2], framebc1, framebc1); //Left
            draw_line_colour(argument0[| 1]-1, 0, argument0[| 1]-1, argument0[| 2], framebc1, framebc1); //Right
        }
        { //Border 2
            draw_line_colour(0, 1, argument0[| 1]-3, 1, framebc2, framebc2); //Top
            draw_line_colour(0, argument0[| 2]-2, argument0[| 1]-2, argument0[| 2]-2, framebc2, framebc2); //Bottom
            draw_line_colour(0, 1, 1, argument0[| 2]-2, framebc2, framebc2); //Left
            draw_line_colour(argument0[| 1]-2, 0, argument0[| 1]-2, argument0[| 2]-2, framebc2, framebc2); //Right
        }
    }
    surface_reset_target();
}
draw_surface(argument0[| 0], argument1, argument2);
