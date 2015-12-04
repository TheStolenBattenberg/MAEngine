///MAE_PhysShapeCreateCone(radius, height, axis)

/**
 * Description:
 *   Creates a cone shape.
 *
 * Arguments:
 *   [0] - Radius
 *   [1] - Height
 *   [2] - Up axis. Can be  0, 1, or 2, to correspond with x, y, z.
 *
 * Returns:
 *   Shape ID
 */

return external_call(global.MAB_ShapeCreateCone, argument0, argument1, argument2);
