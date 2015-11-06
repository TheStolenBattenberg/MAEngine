///MAE_PhysShapeCreateTriMesh(buffer, num_triangles, welding_threshold, [convex])

var _p = buffer_get_address(argument[0]);
if(argument_count == 2) return external_call(global.MAB_ShapeCreateTriMesh, _p, argument[1], 0, 0);
if(argument_count == 3) return external_call(global.MAB_ShapeCreateTriMesh, _p, argument[1], argument[2], 0);
return external_call(global.MAB_ShapeCreateTriMesh, _p, argument[1], argument[2], argument[3]);
