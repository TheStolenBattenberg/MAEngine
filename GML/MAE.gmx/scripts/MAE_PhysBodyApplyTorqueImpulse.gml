///MAE_PhysBodyApplyTorqueImpulse(body, relative, impulse)
///MAE_PhysBodyApplyTorqueImpulse(body, relative, xvel, yvel, zvel)

/**
 * Description:
 *   Applies torque impulse to a physics body.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Local space(true), or world space(false)
 *   [2] - Torque vector
 *
 * Returns:
 *   Success
 */

if(argument_count == 3){
    var vec = argument[2];
    return external_call(global.MAB_BodyApplyTorqueImpulse, argument[0], vec[0], vec[1], vec[2], argument[1]);
}
return external_call(global.MAB_BodyApplyTorqueImpulse, argument[0], argument[2], argument[3], argument[4], argument[1]);
