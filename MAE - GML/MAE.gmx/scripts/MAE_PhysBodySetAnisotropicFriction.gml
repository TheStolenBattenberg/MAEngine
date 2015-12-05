///MAE_PhysBodySetAnisotropicFriction(body, x, y, z)
///MAE_PhysBodySetAnisotropicFriction(body, vec)

/**
 * Description:
 *   Sets the ansitropic friction of a physics body.
 *
 * Arguments:
 *   [0]   - Body
 *   [1-3] - X, Y, Z friction
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var vec = argument[1];
    return external_call(global.MAB_BodySetAnisotropicFriction, argument[0], vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_BodySetAnisotropicFriction, argument[0], argument[1], argument[2], argument[3]);
