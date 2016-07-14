///MAE_PhysShapeAddChild(parent_shape,child_shape,posx,posy,posz);

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

return external_call(global._MAB_ShapeAddChild, argument0, argument1, argument2, argument3, argument4, 0, 0, 0, 1);
