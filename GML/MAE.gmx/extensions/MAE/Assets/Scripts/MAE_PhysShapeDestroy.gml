///MAE_PhysShapeDestroy(shape,destroy_children = false);

/**
 * Description:
 *   Destroys a shape, and optionally destroys child shapes if the shape is a compound shape.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Destroy children
 *
 * Returns:
 *   Success
 */

var _destroy_children = false;

if (argument_count > 1)
    _destroy_children = argument[1];

return external_call(global._MAB_ShapeDestroy, argument[0], _destroy_children);
