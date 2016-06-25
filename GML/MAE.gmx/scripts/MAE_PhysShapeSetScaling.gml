///MAE_PhysShapeSetScaling(shape, x, y, z)
///MAE_PhysShapeSetScaling(shape, vec)

/**
 * Description:
 *   Sets the scaling of a shape. Please note that not all shapes support non-uniform scaling.
 *
 * Arguments:
 *   [0]   - Shape
 *   [1-3] - Scaling
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var vec = argument[1];
    return external_call(global.MAB_ShapeSetScaling, argument[0], vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_ShapeSetScaling, argument[0], argument[1], argument[2], argument[3]);

