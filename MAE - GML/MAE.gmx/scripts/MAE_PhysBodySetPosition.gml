///MAE_PhysBodySetPosition(body, position)
///MAE_PhysBodySetPosition(body, x, y, z)

/**
 * Description:
 *   Sets the position of the physics body in the world.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Position as a vector
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var vec = argument[1];
    return external_call(global.MAB_BodySetPosition, argument[0], vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_BodySetPosition, argument[0], argument[1], argument[2], argument[3]);
