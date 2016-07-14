///MAE_PhysShapeSetScalingVector(shape,scale);

/**
 * Description:
 *   Sets the scaling of a shape. Please note that not all shapes support non-uniform scaling.
 *
 * Arguments:
 *   [1] - Shape
 *
 * Returns:
 *   Success
 */

var scal = argument1;

return external_call(global._MAB_ShapeSetScaling, argument0, scal[0], scal[1], scal[2]);
