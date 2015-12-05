///MAE_PhysWorldStep(timestep, max_sub_steps, fixed_timestep)

/**
 * Description:
 *   Steps the simulation by a specified amount of time with optional sub-steps. Typically the timestep is the amount of time between calls.
 *
 *   If your game uses a fixed frame rate, then you don't need to use the last 2 arguments.
 *      Example: MAE_PhysWorldStep(1/room_speed, 0, 0);
 *
 *   If you want to increase simulation stability and accuraccy, you can use sub-steps.
 *      Example: MAE_PhysWorldStep(1/60, 2, 1/120);
 *
 *   If your game uses a variable frame rate, you have 2 options:
 *
 *   Simply advance the simulation by the delta time. This will give slightly different results depending on frame rate.
 *      Example: MAE_PhysWorldStep(delta_time*0.000001, 0, 0)
 *
 *   Use a fixed timestep, which will give the same results regardless of framerate, but uses interpolation when the simulation timing doesn't match the framerate.
 *      Example: MAE_PhysWorldStep(delta_time*0.000001, 4, 1/60)
 *
 * Arguments:
 *   [0] - The amount of time to simulate, in seconds.
 *   [1] - The maximum number of substeps, must be larger than 1 to enable interpolation.
 *   [2] - The amount of time each step will simulate. Pass in 0 to disable substepping.
 *
 * Returns:
 *   Success
 */
 
return external_call(global.MAB_WorldStep, argument0, argument1, argument2);
