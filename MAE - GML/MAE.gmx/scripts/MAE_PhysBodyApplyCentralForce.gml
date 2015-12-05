///MAE_PhysBodyApplyCentralForce(body, relative, force)
///MAE_PhysBodyApplyCentralForce(body, relative, xvel, yvel, zvel)

/**
 * Description:
 *   Applies a force to the center of a physics body.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Local space(true), or world space(false)
 *   [2] - Force as a vector
 *
 * Returns:
 *   Success
 */

if(argument_count == 3){
    var vec = argument[2];
    return external_call(global.MAB_BodyApplyCentralForce, argument[0], vec[0], vec[1], vec[2], argument[1]);
}
return external_call(global.MAB_BodyApplyCentralForce, argument[0], argument[2], argument[3], argument[4], argument[1]);
