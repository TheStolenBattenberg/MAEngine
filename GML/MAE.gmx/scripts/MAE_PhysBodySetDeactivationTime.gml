///MAE_PhysBodySetDeactivationTime(body, time)

/**
 * Description:
 *   Sets the amount of time a body will wait before sleeping when it isn't moving.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Time
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_BodySetDeactivationTime, argument0, argument1);
