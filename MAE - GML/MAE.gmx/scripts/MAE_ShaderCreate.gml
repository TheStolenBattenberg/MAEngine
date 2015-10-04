///MAE_ShaderCreate(vertex_shader_code, pixel_shader_code, type);

/**
 * To-do:
 *      Add Description.
 *
 */
switch(argument2)
{
    case SHADER_HLSL9:
        show_debug_message("Compiling and Setting HLSL9 shader!");
        
        result = external_call(global.MADX9_ShaderCreateHLSL9, argument0, argument1);
        if(result == 0)
        {
            show_debug_message("Failed to compile shader.");
            return 0;
        }
        show_debug_message("Compiled Vertex & Pixel Shader ID: "+string(result));
        return result;
    break;
    
    default:
        show_debug_message("Invalid Shader Type!");
        return 0;
    break;
}
