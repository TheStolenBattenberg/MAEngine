///MAE_LightSetAttenuation(Index, Att0, Att1, Att2);

/**
 * Description:
 *   Sets the attenuation of a previously created light.
 *
 * Arguments:
 *   [1] - Light Index.
 *   [2] - Att0.
 *   [3] - Att1.
 *   [4] - Att2.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
external_call(global.MADX9_LightSetAttenuation0, argument0, argument1);
external_call(global.MADX9_LightSetAttenuation1, argument0, argument2);
external_call(global.MADX9_LightSetAttenuation2, argument0, argument3);
return 1;
