///MAE_PhysShapeUpdateChildTransform(parent_shape,index,posx,posy,posz);

/**
 * Description:
 *   Changes the transform of a child of a compound shape.
 *
 * Arguments:
 *   [1] - Parent shape
 *   [2] - Child index
 *   [3] - Position as vector
 *   [4] - Rotation as quaternion
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_ShapeUpdateChildTransform, argument0, argument1, argument2, argument3, argument4, 0, 0, 0, 1);
