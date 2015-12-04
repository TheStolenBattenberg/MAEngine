///MAE_PhysShapeCreateTriMesh(buffer, [convex], [welding_threshold])

/**
 * Description:
 *   Creates a triangle mesh shape. If made convex, the shape can be used for a dynamic body.
 *   If it is not convex, it can be used only for static bodies.
 *
 * Arguments:
 *   [0] - Buffer containing triangles
 *   [1] - Convex
 *   [2] - Vertex welding threshold
 *
 * Returns:
 *   Shape ID
 */

var _p = buffer_get_address(argument[0]);
var _s = buffer_tell(_p) div 36;
if(argument_count == 1) return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, 0, 0);
if(argument_count == 2) return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, argument[1], 0);
return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, argument[1], argument[2]);
