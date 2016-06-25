///MAE_PhysBodyApplyImpulse(body, position, impulse)
///MAE_PhysBodyApplyImpulse(body, x, y, z, xvel, yvel, zvel)

/**
 * Description:
 *   Applies an impulse to a physics body at the specified point in local space.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Position as a vector
 *   [2] - Force as a vector
 *
 * Returns:
 *   Success
 */

if(argument_count == 3){
    var vec = argument[1];
    var vec2 = argument[2];
    return external_call(global.MAB_BodySetApplyImpulse, argument[0], vec[0], vec[1], vec[2], vec2[0], vec2[1], vec2[2]);
}
return external_call(global.MAB_BodyApplyImpulse, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6]);
