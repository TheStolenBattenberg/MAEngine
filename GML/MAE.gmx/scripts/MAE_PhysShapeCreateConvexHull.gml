///MAE_PhysShapeCreateConvexHull(buffer)

/**
 * Description:
 *   Creates a convex hull shape around a point cloud. This shape can be used for dynamic bodies.
 *
 * Arguments:
 *   [0] - Buffer of points
 *
 * Returns:
 *   Shape ID
 */

return external_call(global.MAB_ShapeCreateConvexHull, buffer_get_address(argument0), buffer_tell(argument0) div 12);
