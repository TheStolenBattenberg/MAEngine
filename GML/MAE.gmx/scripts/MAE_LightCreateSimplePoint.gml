///MAE_LightCreateSimplePoint(x, y, z, range, colour);

/**
 * Description:
 *   Creates a simple point light. Can be edited with MAE_LightSet* Functions.
 *
 * Arguments:
 *   [1] - X Position.
 *   [2] - Y Position.
 *   [3] - Z Position.
 *   [4] - Range.
 *   [5] - Colour.
 *
 * Returns:
 *   Light Index.
 */
 
var lt = MAE_LightCreate(LIGHT_POINT);
MAE_LightSetDiffuse(lt, colour_get_red(argument4), colour_get_green(argument4), colour_get_blue(argument4), 255);
MAE_LightSetPosition(lt, argument0, argument1, argument2);
MAE_LightSetRange(lt, argument3);
MAE_LightSetAttenuation(lt, 0.0, 0.05, 0.0);
return lt;
