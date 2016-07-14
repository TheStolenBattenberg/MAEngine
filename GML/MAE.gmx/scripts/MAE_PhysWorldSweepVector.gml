///MAE_PhysWorldSweepVector(shape,start,end,group = -1,mask = -1);

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

if (argument_count > 3)
    _group = argument[3];

if (argument_count > 4)
    _mask = argument[4];

var startVec = argument[1], endVec = argument[2];

return external_call(global._MAB_WorldSweep, argument[0], startVec[0], startVec[1], startVec[2], endVec[0], endVec[1], endVec[2], _group, _mask);
