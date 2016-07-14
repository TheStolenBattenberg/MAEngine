///MAE_PhysBodySetUserIndex(body,number);

/**
 * Description:
 *   Gives a physics body a user defined index. It can be any unsigned integer of your choice. This is useful to link a GM instance with a physics body. After a collision check, you could then easily check which instance was hit.
 *
 * Arguments:
 *   [1] - Body
 *   [2] - Number
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_BodySetUserIndex, argument0, argument1);
