///MAE_ShaderCreate(vertex_shader_code, pixel_shader_code, type);

/**
 * Description:
 *   Creates a shader from strings.
 *
 * Arguments:
 *   [1] - Vertex shader code
 *   [2] - Pixel shader code (same as fragment shader in GLSL ES)
 *   [3] - Type (SHADER_*)
 *
 * Returns:
 *   -1 on Error, shader index on success.
 */

switch(argument2)
{
    case SHADER_HLSL9:        
        result = external_call(global.MADX9_ShaderCreateHLSL9, argument0, argument1);
        show_debug_message(result);  
        return result;
    break;
    
    case SHADER_ASM:
        result = external_call(global.MADX9_ShaderCreateASM, argument0, argument1);
        show_debug_message(result);
        return result;
    break;
    
    case SHADER_FILE:
        show_debug_message("Unimplemented.");
        return 0;
    break;
    
    default:
        show_debug_message("Invalid Shader Type!");
        return 0;
    break;
}
