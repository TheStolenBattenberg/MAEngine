///MAE_PhysShapeCreateTriMesh(buffer, [convex], [welding_threshold])

var _p = buffer_get_address(argument[0]);
var _s = buffer_tell(_p) div 36;
if(argument_count == 1) return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, 0, 0);
if(argument_count == 2) return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, argument[1], 0);
return external_call(global.MAB_ShapeCreateTriMesh, _p, _s, argument[1], argument[2]);
