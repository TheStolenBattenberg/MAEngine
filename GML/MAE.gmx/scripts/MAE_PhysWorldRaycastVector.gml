///MAE_PhysWorldRaycastVector(start,end,group = -1,mask = -1);

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

if (argument_count > 2)
    _group = argument[2];

if (argument_count > 3)
    _mask = argument[3];

var startVec = argument[0], endVec = argument[1];

return external_call(global._MAB_WorldRaycast, startVec[0], startVec[1], startVec[2], endVec[0], endVec[1], endVec[2], _group, _mask);
