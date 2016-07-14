///MAE_PhysBodySetLinearFactor(body,x,y,z);

/**
 * Description:
 *   Sets the linear factor of a physics body. This can be used to restrict movement per axis. You could limit the physics engine to a 2D plane, for example.
 *
 * Arguments:
 *   [1] - Body
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_BodySetLinearFactor, argument0, argument1, argument2, argument3);
