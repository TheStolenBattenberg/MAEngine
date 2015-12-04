///MAE_PhysShapeUpdateChildTransform(parent_shape, index, position, rotation)
///MAE_PhysShapeUpdateChildTransform(parent_shape, index, x, y, z, rotation)

/**
 * Description:
 *   Changes the transform of a child of a compound shape.
 *
 * Arguments:
 *   [0] - Parent shape
 *   [1] - Child index
 *   [2] - Position as vector
 *   [3] - Rotation as quaternion
 *
 * Returns:
 *   Success
 */

var rot = argument[3];
if(argument_count == 4){
    var vec = argument[2];
    return external_call(global.MAB_ShapeUpdateChildTransform, argument[0], argument[1], vec[0], vec[1], vec[2], rot[0], rot[1], rot[2], rot[3]);
}
return external_call(global.MAB_ShapeUpdateChildTransform, argument[0], argument[1], argument[2], argument[3], argument[4], rot[0], rot[1], rot[2], rot[3]);

