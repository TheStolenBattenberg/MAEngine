///MAE_PhysBodyGetDeactivationTime(body)

/**
 * Description:
 *   Gets the deactivation time of a physics body. When a body has stopped moving, it will wait this amount of time before sleeping.
 *
 * Arguments:
 *   [0] - Body
 *
 * Returns:
 *   Real
 */

return external_call(global.MAB_BodyGetDeactivationTime, argument0);
