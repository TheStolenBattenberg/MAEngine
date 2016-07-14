///MAE_PhysBodySetAnisotropicFrictionVector(body,friction);

/**
 * Description:
 *   Sets the ansitropic friction of a physics body.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Success
 */

var vec = argument1;

return external_call(global._MAB_BodySetAnisotropicFriction, argument0, vec[0], vec[1], vec[2]);
