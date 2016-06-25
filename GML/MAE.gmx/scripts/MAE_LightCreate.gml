///MAE_LightCreate(Type);

/**
 * Description:
 *   Creates an empty light.
 *
 * Arguments:
 *   [1] - Light Type (LIGHT_POINT, LIGHT_SPOT, LIGHT_DIRECTIONAL).
 *
 * Returns:
 *   Light Index.
 */
 
return external_call(global.MADX9_LightCreate, argument0);
