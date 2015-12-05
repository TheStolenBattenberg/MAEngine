///MAE_PhysBodySetGravity(body, x, y, z)
///MAE_PhysBodySetGravity(body, vec)

/**
 * Description:
 *   Overrides the world gravity on a body with a different gravity force.
 *
 * Arguments:
 *   [0]   - Body
 *   [1-3] - X, Y, Z gravity
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var vec = argument[1];
    return external_call(global.MAB_BodySetGravity, argument[0], vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_BodySetGravity, argument[0], argument[1], argument[2], argument[3]);
