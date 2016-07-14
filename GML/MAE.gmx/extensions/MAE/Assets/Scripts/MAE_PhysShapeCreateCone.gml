///MAE_PhysShapeCreateCone(radius,height,axis);

/**
 * Description:
 *   Creates a cone shape.
 *
 * Arguments:
 *   [1] - Radius
 *   [2] - Height
 *   [3] - Up axis. Can be  0, 1, or 2, to correspond with x, y, z.
 *
 * Returns:
 *   Shape ID
 */

return external_call(global._MAB_ShapeCreateCone, argument0, argument1, argument2);
