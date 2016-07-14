///MAE_PhysWorldRaycast(startx,starty,startz,endx,endy,endz,group = -1,mask = -1);

/**
 * Description:
 *   Checks for collisions by casting a ray between 2 points, with an optional collision mask. Use the MAE_PhysWorldHit functions to get more information about the collision.
 *
 * Arguments:
 *   [1] - Starting point as a vector
 *   [2] - End point as a vector
 *
 * Returns:
 *   1 on collision, 0 if nothing was hit.
 */

var _group = -1, _mask = -1;

if (argument_count > 6)
    _group = argument[6];

if (argument_count > 7)
    _mask = argument[7];

return external_call(global._MAB_WorldRaycast, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], _group, _mask);
