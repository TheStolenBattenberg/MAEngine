///MAE_PhysShapeSetMargin(shape,margin);

/**
 * Description:
 *   Sets the margin of a shape. The margin is an extra space around a shape. It is sometimes desirable to make the base shape smaller to make room for a larger margin, because this results in smoothly rounded corners.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Margin
 *
 * Returns:
 *   Success
 */

return external_call(global._MAB_ShapeSetMargin, argument0, argument1);
