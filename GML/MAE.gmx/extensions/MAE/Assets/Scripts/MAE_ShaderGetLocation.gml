///MAE_ShaderGetLocation(shader_index,str);

/**
 * Description:
 *   Finds a constant by string.
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Name of the location
 *
 * Returns:
 *   -1 on Error, constant index on success.
 */

return external_call(global._MAE_ShaderGetLocation, argument0, argument1);
