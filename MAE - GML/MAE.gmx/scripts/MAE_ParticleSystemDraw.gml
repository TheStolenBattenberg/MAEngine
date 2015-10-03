///MAE_ParticleSystemDraw(particle_system, particle);

/**
 * TO-DO:
 * - Add Error Handling
 * - Write Description
 */

d3d_set_culling(false);
draw_set_alpha(argument1[| 10]);
draw_set_blend_mode(argument1[| 12]);
{
    vertex_submit(argument0[| 1], pr_trianglelist, argument1[| 1]);
}
draw_set_blend_mode(bm_normal);
draw_set_alpha(1);
d3d_set_culling(true);
