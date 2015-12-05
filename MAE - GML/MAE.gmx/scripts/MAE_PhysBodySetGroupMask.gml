///MAE_PhysBodySetGroupMask(body, group, mask)

/**
 * Description:
 *   Sets collision group and mask of a physics body. The group and mask are bitmasks. Interally, they are stored as signed ints, so you can have up to 15 groups and 15 masks.
 *   To check if 2 bodies can collide, a bitwise AND is performed between bodyA's mask, and bodyB's group. The collision masks must match both ways for there to be a collision.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Group
 *   [2] - Mask
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_BodySetGroupMask, argument0, argument1, argument2);
