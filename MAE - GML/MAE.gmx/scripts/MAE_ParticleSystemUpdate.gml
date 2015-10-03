///MAE_ParticleSystemUpdate(particle_system, particle, step, offset_x, offset_y, offsex_z);

/**
 * TO-DO:
 * - Add Error Handling
 * - Write Description
 */
vertex_delete_buffer(argument0[| 1]);
argument0[| 1] = vertex_create_buffer();
vertex_begin(argument0[| 1], vpartformat)
{
    buffer_seek(argument0[| 0], buffer_seek_start, 0);
    var buffersize = buffer_get_size(argument0[| 0])/12;
    
    var i =0;
    repeat(buffersize)
    {
        i++;
        var life = buffer_read(argument0[| 0], buffer_u16)-argument2;
        
        buffer_seek(argument0[| 0], buffer_seek_start, buffer_tell(argument0[| 0])-2);
        buffer_write(argument0[| 0], buffer_u16, life);
        
        if(life <= 0)
        {
            show_debug_message("Particle "+string(i) + ": Updated.");
            buffer_seek(argument0[| 0], buffer_seek_start, buffer_tell(argument0[| 0])-2);
            
            buffer_write(argument0[| 0], buffer_u16, random_range(argument1[| 13], argument1[| 14]));
            buffer_write(argument0[| 0], buffer_s16, random_range(-argument0[| 2], argument0[| 2]));
            buffer_write(argument0[| 0], buffer_s16, random_range(-argument0[| 3], argument0[| 3]));
            buffer_write(argument0[| 0], buffer_s16, random_range(-argument0[| 4], argument0[| 4]));
            buffer_write(argument0[| 0], buffer_f32, random_range(argument1[| 2], argument1[| 3]));
            
            buffer_seek(argument0[| 0], buffer_seek_start, buffer_tell(argument0[| 0])-10);
        }

        var xx = argument3 + buffer_read(argument0[| 0], buffer_s16);
        var yy = argument4 + buffer_read(argument0[| 0], buffer_s16);
        var zz = argument5 + buffer_read(argument0[| 0], buffer_s16);
        var size = buffer_read(argument0[| 0], buffer_f32);
        

        //Triangle 01
        vertex_position_3d(argument0[| 1], xx-size, yy-size, zz);
        vertex_texcoord(argument0[| 1], 0, 0);
        
        vertex_position_3d(argument0[| 1], xx-size, yy+size, zz);
        vertex_texcoord(argument0[| 1], 0, 1);
        
        vertex_position_3d(argument0[| 1], xx+size, yy-size, zz);
        vertex_texcoord(argument0[| 1], 1, 0);
        
        //Triangle 02
        vertex_position_3d(argument0[| 1], xx+size, yy-size, zz);
        vertex_texcoord(argument0[| 1], 1, 0)
        
        vertex_position_3d(argument0[| 1], xx-size, yy+size, zz);
        vertex_texcoord(argument0[| 1], 0, 1);

        vertex_position_3d(argument0[| 1], xx+size, yy+size, zz);
        vertex_texcoord(argument0[| 1], 1, 1);
    }
}
vertex_end(argument0[| 1]);
vertex_freeze(argument0[| 1]);
