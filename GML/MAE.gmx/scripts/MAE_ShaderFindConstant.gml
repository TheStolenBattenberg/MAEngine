///MAE_ShaderFindConstant(shader_index,name)

/**
 * Description:
 *   Finds a constant by string.
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Name of the constant
 *
 * Returns:
 *   -1 on Error, constant index on success.
 */

return external_call(global.__MAE_ShaderFindConstant, argument0, argument1);
