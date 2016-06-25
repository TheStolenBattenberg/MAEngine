///MAE_ShaderSetConstantFloat(index,shd,c,val)

/**
 * Description:
 *   Sets a constant to a float value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Shader type (SHD_*)
 *   [3] - Index of the constant
 *   [4] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_ShaderSetConstantFloat, argument0, argument1, argument2, argument4);
