///MAE_ShaderCreate(vertshd,pixelshd);

/**
 * Description:
 *   Creates a shader from strings
 *
 * Arguments:
 *   [1] - Vertex Shader Code
 *   [2] - Pixel Shader Code
 *
 * Returns:
 *   -1 on Error, shader index on success
 */

return external_call(global._MAE_ShaderCreate, argument0, argument1);
