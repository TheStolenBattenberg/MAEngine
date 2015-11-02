///MAE_Init(flags,[dll])
global.DLL_MADX9 = "MA_DX9.dll";

if (argument_count > 1 && is_string(argument[1]))
    global.DLL_MADX9 = argument[1];

// Private
global.MADX9_Init = external_define(global.DLL_MADX9, "MADX9_Init", dll_cdecl, ty_real, 1, ty_real);

if (argument[0] & INIT_RENDER)
{
    //Shaders
    global.MADX9_ShaderCreateHLSL9  = external_define(global.DLL_MADX9, "MADX9_ShaderCreateHLSL9", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_ShaderSetHLSL9     = external_define(global.DLL_MADX9, "MADX9_ShaderSetHLSL9", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_ShaderResetHLSL9   = external_define(global.DLL_MADX9, "MADX9_ShaderResetHLSL9", dll_cdecl, ty_real, 0);
    global.MADX9_ShaderDestroyHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderDestroyHLSL9", dll_cdecl, ty_real, 1, ty_real);
    
    //Lights
    global.MADX9_LightCreate          = external_define(global.DLL_MADX9, "MADX9_LightCreate", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_LightSetDiffuse      = external_define(global.DLL_MADX9, "MADX9_LightSetDiffuse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_LightSetPosition     = external_define(global.DLL_MADX9, "MADX9_LightSetPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_LightSetRange        = external_define(global.DLL_MADX9, "MADX9_LightSetRange", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation0 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation0", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation1 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation1", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation2 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation2", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightEnable          = external_define(global.DLL_MADX9, "MADX9_LightEnable", dll_cdecl, ty_real, 2, ty_real, ty_real);
    
    //MD2
    global.MADX9_MD2Load   = external_define(global.DLL_MADX9, "MADX9_MD2Load", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_MD2Render = external_define(global.DLL_MADX9, "MADX9_MD2Render", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
}

if (argument[0] & INIT_HOOKS)
{
    //Hooks
    global.MADX9_HooksCreate      = external_define(global.DLL_MADX9, "MADX9_HooksCreate", dll_cdecl, ty_real, 0);
    global.MADX9_HooksDestroy     = external_define(global.DLL_MADX9, "MADX9_HooksDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_HooksApply       = external_define(global.DLL_MADX9, "MADX9_HooksApply", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_HooksRemove      = external_define(global.DLL_MADX9, "MADX9_HooksRemove", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_HooksMakeCurrent = external_define(global.DLL_MADX9, "MADX9_HooksMakeCurrent", dll_cdecl, ty_real, 1, ty_real);
}

external_call(global.MADX9_Init, window_device());
