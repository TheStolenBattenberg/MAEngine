///MAE_PhysWorldOverlapQuat(shape,x,y,z,quaternion,group = -1,mask = -1);

/**
 * Description:
 *   Checks for overlaps in the world with a shape, with an optional collision mask. Use the MAE_PhysWorldHitBody(n) to get the ID's of all the bodies in the world that overlapped.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Position as a vector
 *   [3] - Rotation as a quaternion.
 *
 * Returns:
 *   The number of overlaps.
 */

var _group = -1, _mask = -1;

if (argument_count > 5)
    _group = argument[5];

if (argument_count > 6)
    _mask = argument[6];

var quat = argument[4];

return external_call(global._MAB_WorldOverlap, argument[1], argument[2], argument[3], quat[0], quat[1], quat[2], quat[3], _group, _mask);
