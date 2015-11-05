///MAE_PhysShapeDestroy(shape, [destroy_children])

if(argument_count == 1) return external_call(global.MAB_ShapeDestroy, argument[0], false);
else return external_call(global.MAB_ShapeDestroy, argument[0], argument[1]);

