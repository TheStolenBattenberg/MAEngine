///MAE_ShaderSetConstantFloat(index,c,val);

/**
 * Description:
 *   Sets a constant to a float value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Index of the constant
 *   [3] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global._MAE_ShaderSetConstantFloat, argument0, argument1, argument2);
