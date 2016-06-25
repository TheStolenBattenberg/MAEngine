///MAE_PhysWorldSetGravity(x, y, z)
///MAE_PhysWorldSetGravity(vec)

/**
 * Description:
 *   Sets the gravity of the physics world. Pass in 3 reals or a vector.
 *
 * Arguments:
 *   [0-3] - Gravity vector.
 *
 * Returns:
 *   Success
 */

if(argument_count == 1){
    var vec = argument[0];
    return external_call(global.MAB_WorldSetGravity, vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_WorldSetGravity, argument[0], argument[1], argument[2]);
