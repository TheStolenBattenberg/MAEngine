///MAE_Init(flags)


global.DLL_MADX9 = "MA_DX9.dll";
if(argument0 == 1 || argument0 == 3 || argument0 == 5 || argument0 == 7)
{
    //Private
    global.MADX9_Init = external_define(global.DLL_MADX9, "MADX9_Init", dll_cdecl, ty_real, 1, ty_real);
    
    //Shaders
    global.MADX9_ShaderCreateHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderCreateHLSL9", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_ShaderSetHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderSetHLSL9", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_ShaderResetHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderResetHLSL9", dll_cdecl, ty_real, 0);
    global.MADX9_ShaderDestroyHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderDestroyHLSL9", dll_cdecl, ty_real, 1, ty_real);
    
    //Lights
    global.MADX9_LightCreate = external_define(global.DLL_MADX9, "MADX9_LightCreate", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_LightSetDiffuse = external_define(global.DLL_MADX9, "MADX9_LightSetDiffuse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_LightSetPosition = external_define(global.DLL_MADX9, "MADX9_LightSetPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    
    //Init MX_DX9.
    external_call(global.MADX9_Init, window_device());
}
