///MAE_PhysWorldOverlapVector(shape,vec,group = -1,mask = -1);

/**
 * Description:
 *   Checks for overlaps in the world with a shape, with an optional collision mask. Use the MAE_PhysWorldHitBody(n) to get the ID's of all the bodies in the world that overlapped.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Position as a vector
 *
 * Returns:
 *   The number of overlaps.
 */

var _group = -1, _mask = -1;

if (argument_count > 2)
    _group = argument[2];

if (argument_count > 3)
    _mask = argument[3];

var vec = argument[1];

return external_call(global._MAB_WorldOverlap, vec[0], vec[1], vec[2], 0, 0, 0, 1, _group, _mask);
