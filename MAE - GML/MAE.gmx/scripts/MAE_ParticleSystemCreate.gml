///MAE_ParticleSystemCreate(particle, area, count, distribution);

/**
 * TO-DO:
 * - Add Error Handling
 * - Write Description
 */
var ds = ds_list_create();
ds[| 0] = buffer_create(12*argument2, buffer_fixed, 1)
{
    switch(argument3)
    {
        case PARTICLE_DISTRIBUTION_RANDOM:
            repeat(argument2)
            {
                buffer_write(ds[| 0], buffer_u16, random_range(argument0[| 13], argument0[| 14]));
                buffer_write(ds[| 0], buffer_s16, random_range(-argument1[| 0], argument1[| 0]));
                buffer_write(ds[| 0], buffer_s16, random_range(-argument1[| 1], argument1[| 1]));
                buffer_write(ds[| 0], buffer_s16, random_range(-argument1[| 2], argument1[| 2]));
                buffer_write(ds[| 0], buffer_f32, random_range(argument0[| 2], argument0[| 3]));
            }
        break;
        
        case PARTICLE_DISTRIBUTION_SPHERE:
            var i = 0;
            repeat(argument2)
            {
                var value = (360/argument2) * i;
                buffer_write(ds[| 0], buffer_u16, random_range(argument0[| 13], argument0[| 14]));
                buffer_write(ds[| 0], buffer_s16, lengthdir_x(random_range(0, argument1[| 0]), (360/argument2) * i));
                buffer_write(ds[| 0], buffer_s16, lengthdir_y(random_range(0, argument1[| 1]), (360/argument2) * i));
                buffer_write(ds[| 0], buffer_s16, random_range(-argument1[| 2], argument1[| 2]));
                buffer_write(ds[| 0], buffer_f32, random_range(argument0[| 2], argument0[| 3]));
                
                i++;
            }
        break;
    }
}
ds[| 2] = argument1[| 0];
ds[| 3] = argument1[| 1]; 
ds[| 4] = argument1[| 2]; 
ds_list_destroy(argument1);

vertex_format_begin();
vertex_format_add_position_3d();
vertex_format_add_textcoord();
vpartformat = vertex_format_end();

ds[| 1] = vertex_create_buffer();

return ds;
