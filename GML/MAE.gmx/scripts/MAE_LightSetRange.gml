///MAE_LightSetRange(Index, Range);

/**
 * Description:
 *   Sets the range of a previously created light.
 *
 * Arguments:
 *   [1] - Light Index.
 *   [2] - Range.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
return external_call(global.MADX9_LightSetRange, argument0, argument1);
