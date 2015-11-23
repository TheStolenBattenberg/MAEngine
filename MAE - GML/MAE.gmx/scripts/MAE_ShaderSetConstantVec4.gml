///MAE_ShaderSetConstantVec4(index,shd,c,vec)

/**
 * Description:
 *   Sets a constant to a vec4 value
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

return external_call(global.MADX9_ShaderSetConstantVec4, argument0, argument1, argument2, argument3[0], argument3[1], argument3[2], argument3[3]);
