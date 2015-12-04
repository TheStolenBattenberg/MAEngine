///MAE_PhysWorldStep(timestep, max_sub_steps, fixed_timestep)

/**
 * Description:
 *   Steps the simulation by a specified amount of time, in seconds, with optional sub-steps.
 *   Typically timestep is the time since the last time it was called.
 *
 *   If your game uses a fixed frame rate, then you don't need to use the last 2 arguments.
 *      Example: MAE_PhysWorldStep(1/room_speed, 0, 0);
 *
 *   If your game uses a variable frame rate, you have 2 options:
 *
 *   Simply advance the simulation by the delta time. This will give slightly different results depending on frame rate.
 *      Example: MAE_PhysWorldStep(delta_time*0.0001, 0, 0)
 *
 *   Advance the simulation by fixed_timestep until timestep is reached, by splitting timestep into substeps if necessary.
 *   This gives same results regardless of framerate.
 *      Example: MAE_PhysWorldStep(delta_time*0.0001, 4, 1/60)
 *
 * Arguments:
 *   [0] - The amount of time to simulate.
 *   [1] - The maximum number of substeps.
 *   [2] - The amount of time each step will simulate. Pass in 0 to disable substepping.
 *
 * Returns:
 *   Success
 */
 
return external_call(global.MAB_WorldStep, argument0, argument1, argument2);
