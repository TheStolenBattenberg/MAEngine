///MAE_PhysWorldCreate(use_interpolation = false);

/**
 * Description:
 *   Creates the physics world. You have the option to interpolate the transformations of physics bodies between frames. This is useful if you are using a variable frame rate with a fixed timestep.
 *
 * Arguments:
 *   [1] - (optional) Use interpolation?
 *
 * Returns:
 *   Success
 */

var _use_interpolation = false;

if (argument_count > 0)
    _use_interpolation = argument[0];

return external_call(global._MAB_WorldCreate, _use_interpolation);
