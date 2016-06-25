///MAE_PhysBodyGetAngularVelocity(body)

/**
 * Description:
 *   Gets the angular velocity of a physics body.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   Vector
 */

external_call(global.MAB_BodyGetAngularVelocity, argument0);
var vec;
vec[0] = external_call(global.MAB_Vec, 0);
vec[1] = external_call(global.MAB_Vec, 1);
vec[2] = external_call(global.MAB_Vec, 2);
return vec;
