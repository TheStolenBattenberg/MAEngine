///MAE_PhysShapeSetMargin(shape, margin)

/**
 * Description:
 *   Sets the margin of a shape. The margin is an extra space around a shape.
 *   It is sometimes desirable to make the base shape smaller to make room for a larger margin, because this results in smoothly rounded corners.
 *
 * Arguments:
 *   [0] - Shape
 *   [1] - Margin
 *
 * Returns:
 *   Success
 */

return external_call(global.MAB_ShapeSetMargin, argument0, argument1);

