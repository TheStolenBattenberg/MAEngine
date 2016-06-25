///MAE_PhysBodyGetUserIndex(body)

/**
 * Description:
 *   Gets the user index of a physics body. If you have not set this, it will default to 0.
 *   The user index is for your own use, and can be any integer of your choosing.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   Integer
 */

return external_call(global.MAB_BodyGetUserIndex, argument0);
