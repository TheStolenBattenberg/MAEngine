///MAE_PhysShapeAddChildVectorQuat(parent_shape,child_shape,pos,rotation);

/**
 * Description:
 *   Adds a child shape to a compound shape with an offset and rotation.
 *
 * Arguments:
 *   [1] - Parent shape
 *   [2] - Child shape
 *   [3] - Position as vector
 *   [4] - Rotation as quaternion
 *
 * Returns:
 *   Child index
 */

var pos = argument2, quat = argument3;

return external_call(global._MAB_ShapeAddChild, argument0, argument1, pos[0], pos[1], pos[2], quat[0], quat[1], quat[2], quat[3]);
