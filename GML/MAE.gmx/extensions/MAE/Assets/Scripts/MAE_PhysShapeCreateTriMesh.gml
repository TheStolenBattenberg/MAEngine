///MAE_PhysShapeCreateTriMesh(buffer,convex = false,welding_threshold = 0);

/**
 * Description:
 *   Creates a triangle mesh shape. If made convex, the shape can be used for a dynamic body. If it is not convex, it can be used only for static bodies.
 *
 * Arguments:
 *   [1] - Buffer containing triangles
 *   [2] - Convex
 *   [3] - Vertex welding threshold
 *
 * Returns:
 *   Shape ID
 */

var _convex = false, _welding_threshold = 0;

if (argument_count > 1)
    _convex = argument[1];

if (argument_count > 2)
    _welding_threshold = argument[2];

return external_call(global._MAB_ShapeCreateTriMesh, buffer_get_address(argument[0]), buffer_tell(argument[0]) div 36, _convex, _welding_threshold);
