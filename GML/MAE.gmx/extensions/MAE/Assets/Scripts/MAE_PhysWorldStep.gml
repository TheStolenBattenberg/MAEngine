///MAE_PhysWorldStep(timestep,max_sub_steps,fixed_timestep);

/**
 * Description:
 *   Steps the simulation by a specified amount of time. Typically the timestep is the amount of time between calls. The physics engine will advance the simulation with increments of fixed_timestep, using sub-steps if necessary. The physics engine has an internal clock that will keep track of any leftover time and apply it the next frame. It is important that timestep is always less than max_sub_steps fixed_timestep, otherwise the simulation will loose time. You don't have to use a fixed timestep. If you set the last 2 parameters to 0 the simulation will simply advance by timestep.
 *
 * Arguments:
 *   [1] - The amount of time to simulate, in seconds.
 *   [2] - The maximum number of substeps, must be larger than 1 to enable interpolation.
 *   [3] - The amount of time each step will simulate. Pass in 0 to disable substepping.
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_WorldStep, argument0, argument1, argument2);
