///MAE_ShaderCompile(index,vertex_shader_code, pixel_shader_code, type);

/**
 * Description:
 *   Creates a shader from strings.
 *
 * Arguments:
 *   [1] - Index of the shader
 *   [2] - Vertex shader code
 *   [3] - Pixel shader code (same as fragment shader in GLSL ES)
 *   [4] - Type (SHADER_*)
 *
 * Returns:
 *   -1 on Error, shader index on success.
 */

switch(argument3)
{
case SHADER_HLSL9:        
    return external_call(global.__MAE_ShaderCompileD3D9HLSL9, argument0, argument1, argument2);
case SHADER_ASM:
    return external_call(global.__MAE_ShaderCompileD3D9ASM, argument0, argument1, argument2);
case SHADER_FILE:
    show_debug_message("Unimplemented.");
    return 0;
default:
    show_debug_message("Invalid Shader Type!");
    return 0;
}
