///MAE_PhysShapeCreateCapsule(radius, height, axis)

/**
 * Description:
 *   Creates a capsule shape.
 *
 * Arguments:
 *   [0] - Radius
 *   [1] - Height
 *   [2] - Up axis. Can be  0, 1, or 2, to correspond with x, y, z.
 *
 * Returns:
 *   Shape ID
 */

return external_call(global.MAB_ShapeCreateCapsule, argument0, argument1, argument2);
