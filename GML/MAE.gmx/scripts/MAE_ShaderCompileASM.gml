///MAE_ShaderCompileASM(index,vertshd,pixelshd);

/**
 * Description:
 *   Creates a shader from strings
 *
 * Arguments:
 *   [1] - Shader ID
 *   [2] - Vertex Shader Code
 *   [3] - Pixel Shader Code
 *
 * Returns:
 *   -1 on Error, shader index on success
 */

return external_call(global._MAE_ShaderCompileD3D9ASM, argument0, argument1, argument2);
