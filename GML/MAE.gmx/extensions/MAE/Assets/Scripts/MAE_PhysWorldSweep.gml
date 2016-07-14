///MAE_PhysWorldSweep(shape,startx,starty,startz,endx,endy,endz,group = -1,mask = -1);

/**
 * Description:
 *   Checks for collisions by casting a convex shape between 2 points, with an optional collision mask. Behaves like a raycast, but casts a shape instead of a point. The shape must be a convex shape. Use the MAE_PhysWorldHit  functions to get more information about the collision.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Starting point as a vector
 *   [3] - End point as a vector
 *
 * Returns:
 *   1 on collision, 0 if nothing was hit.
 */

var _group = -1, _mask = -1;

if (argument_count > 7)
    _group = argument[7];

if (argument_count > 8)
    _mask = argument[8];

return external_call(global._MAB_WorldSweep, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], _group, _mask);
