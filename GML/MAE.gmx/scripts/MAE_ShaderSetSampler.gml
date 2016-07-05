///MAE_ShaderSetSampler(shader_index,constant,sampler)

/**
 * Description:
 *   Sets a sampler.
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Index of the constant
 *   [3] - Sampler
 *
 * Returns:
 *   -1 on Error, constant index on success.
 */

return external_call(global.__MAE_ShaderSetSampler, argument0, argument1, argument2);
