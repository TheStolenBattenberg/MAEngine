///MAE_PhysShapeUpdateChildTransformVectorQuat(parent_shape,index,pos,rotation);

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

var pos = argument2, quat = argument3;

return external_call(global._MAB_ShapeUpdateChildTransform, argument0, argument1, pos[0], pos[1], pos[2], quat[0], quat[1], quat[2], quat[3]);
