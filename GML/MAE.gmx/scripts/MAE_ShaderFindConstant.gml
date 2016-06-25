///MAE_ShaderFindConstant(shader_index,shader,name)

/**
 * Description:
 *   Finds a constant by string.
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Shader type (SHD_*)
 *   [3] - Name of the constant
 *
 * Returns:
 *   -1 on Error, constant index on success.
 */

return external_call(global.MADX9_ShaderFindConstant, argument0, argument1, argument2);
