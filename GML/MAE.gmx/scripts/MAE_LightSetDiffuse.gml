///MAE_LightSetDiffuse(Index, R, G, B, A);

/**
 * Description:
 *   Sets the colour of a previously created light.
 *
 * Arguments:
 *   [1] - Light Index.
 *   [2] - Red Value.
 *   [3] - Green Value.
 *   [4] - Blue Value.
 *   [5] - Alpha Value.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
return external_call(global.MADX9_LightSetDiffuse, argument0, argument1/255, argument2/255, argument3/255, argument4/255);
