///MAE_PhysWorldSetGravityVector(v);

/**
 * Description:
 *   Sets the gravity of the physics world
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   Success
 */

var v = argument0;

return external_call(global._MAB_WorldSetGravity, v[0], v[1], v[2]);
