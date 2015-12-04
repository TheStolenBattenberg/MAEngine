///MAE_PhysShapeDestroy(shape, [destroy_children])

/**
 * Description:
 *   Destroys a shape, and optionally destroys child shapes if the shape is a compound shape.
 *
 * Arguments:
 *   [0] - Shape
 *   [1] - Destroy children
 *
 * Returns:
 *   Success
 */

if(argument_count == 1) return external_call(global.MAB_ShapeDestroy, argument[0], false);
else return external_call(global.MAB_ShapeDestroy, argument[0], argument[1]);

