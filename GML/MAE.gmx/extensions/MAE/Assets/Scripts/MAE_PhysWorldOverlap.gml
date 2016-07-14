///MAE_PhysWorldOverlap(shape,x,y,z,group = -1,mask = -1);

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

if (argument_count > 4)
    _group = argument[4];

if (argument_count > 5)
    _mask = argument[5];

return external_call(global._MAB_WorldOverlap, argument[1], argument[2], argument[3], 0, 0, 0, 1, _group, _mask);
