///MAE_PhysWorldCreate(use_interpolation)

/**
 * Description:
 *   Creates the physics world.
 *   You have the option to interpolate the transformations of physics bodies between frames.
 *   This is useful if you are using a variable frame rate with a fixed timestep.
 *
 * Arguments:
 *   [0] - (optional) Use interpolation?
 *
 * Returns:
 *   Success
 */

if(argument_count == 0) return external_call(global.MAB_WorldCreate, 0);
else return external_call(global.MAB_WorldCreate, argument[0]);

