///MAE_PhysShapeCreateConvexHull(buffer)

return external_call(global.MAB_ShapeCreateConvexHull, buffer_get_address(argument0), buffer_tell(argument0) div 12);
