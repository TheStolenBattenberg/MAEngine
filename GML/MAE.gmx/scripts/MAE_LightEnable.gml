///MAE_LightEnable(LightIndex, Light);

/**
 * Description:
 *   Sets and Enables previously created light.
 *
 * Arguments:
 *   [1] - Light Index.
 *   [2] - Light.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
return external_call(global.MADX9_LightEnable, argument0, argument1);
