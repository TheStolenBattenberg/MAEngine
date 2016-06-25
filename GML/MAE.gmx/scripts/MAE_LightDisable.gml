///MAE_LightDisable(LightIndex);

/**
 * Description:
 *   Disbales light at LightIndex.
 *
 * Arguments:
 *   [1] - Light Index.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
return external_call(global.MADX9_LightDisable, argument0);
