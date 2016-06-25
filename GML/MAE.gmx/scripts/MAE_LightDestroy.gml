///MAE_LightDestroy(Index);

/**
 * Description:
 *   Removes a previously created light from memory.
 *
 * Arguments:
 *   [1] - Light Index.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */

return external_call(global.MADX9_LightDestroy, argument0);
