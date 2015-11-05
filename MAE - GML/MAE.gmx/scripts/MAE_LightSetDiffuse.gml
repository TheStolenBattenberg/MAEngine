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
 
if(argument1 == 0) { var r = 0; }else{ var r = argument1/255; }
if(argument2 == 0) { var g = 0; }else{ var g = argument2/255; }
if(argument3 == 0) { var b = 0; }else{ var b = argument3/255; }
if(argument4 == 0) { var a = 0; }else{ var a = argument4/255; }
return external_call(global.MADX9_LightSetDiffuse, argument0, r, g, b, a);
