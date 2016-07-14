///MAE_PhysBodyApplyImpulse(body,posx,posy,posz,impx,impy,impz);

/**
 * Description:
 *   Applies an impulse to a physics body at the specified point in local space.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Position as a vector
 *   [3] - Force as a vector
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_BodyApplyImpulse, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
