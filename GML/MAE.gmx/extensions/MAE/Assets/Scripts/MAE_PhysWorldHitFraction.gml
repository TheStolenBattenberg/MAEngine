///MAE_PhysWorldHitFraction();

/**
 * Description:
 *   Returns the time of the collision of a sweep or raycast. To get the distance to the collision, multiply the distance between the start and end point of the raycast by this.
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   Real between 0 and 1
 */

return external_call(global._MAB_HitResult, 2);
