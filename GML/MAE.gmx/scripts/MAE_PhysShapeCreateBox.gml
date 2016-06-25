///MAE_PhysShapeCreateBox(xsize, ysize, zsize)

/**
 * Description:
 *   Creates a box shape.
 *
 * Arguments:
 *   [0] - X half size
 *   [1] - Y half size
 *   [2] - Z half size
 *
 * Returns:
 *   Shape ID
 */

return external_call(global.MAB_ShapeCreateBox, argument0, argument1, argument2);
