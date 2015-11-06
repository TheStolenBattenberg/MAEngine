///MAE_ShaderCreate(vertex_shader_code, pixel_shader_code, type);

/**
 * To-do:
 *      Add Description.
 *
 */
switch(argument2)
{
    case SHADER_HLSL9:        
        result = external_call(global.MADX9_ShaderCreateHLSL9, argument0, argument1);       
        return result;
    break;
    
    case SHADER_ASM:
        show_debug_message("Unimplemented.");
        return 0;
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
