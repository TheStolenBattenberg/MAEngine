///MAE_PhysShapeCreatePlane(nx,ny,nz,distance);

/**
 * Description:
 *   Creates an a static plane shape that is solid to infinity on one side.
 *
 * Arguments:
 *   [1] - Distance from origin
 *
 * Returns:
 *   Shape ID
 */

return external_call(global._MAB_ShapeCreatePlane, argument0, argument1, argument2, argument3);
