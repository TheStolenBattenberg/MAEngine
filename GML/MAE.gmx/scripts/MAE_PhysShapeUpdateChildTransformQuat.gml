///MAE_PhysShapeUpdateChildTransformQuat(parent_shape,index,posx,posy,posz,rotation);

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

var quat = argument5;

return external_call(global._MAB_ShapeUpdateChildTransform, argument0, argument1, argument2, argument3, argument4, quat[0], quat[1], quat[2], quat[3]);
