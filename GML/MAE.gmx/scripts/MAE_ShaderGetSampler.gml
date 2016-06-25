///MAE_ShaderGetSampler(shader_index,shader,constant)

/**
 * Description:
 *   Finds a sampler by string.
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Shader type (SHD_*)
 *   [3] - Name of the sampler
 *
 * Returns:
 *   -1 on Error, constant index on success.
 */

return external_call(global.MADX9_ShaderGetSampler, argument0, argument1, argument2);
