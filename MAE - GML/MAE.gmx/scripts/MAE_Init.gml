///MAE_Init()

global.DLL_MADX9 = "MA_DX9.dll";
global.MADX9_Init = external_define(global.DLL_MADX9, "MADX9_Init", dll_cdecl, ty_real, 1, ty_real);
global.MADX9_ShaderCreateHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderCreateHLSL9", dll_cdecl, ty_real, 2, ty_string, ty_string);
global.MADX9_ShaderSetHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderSetHLSL9", dll_cdecl, ty_real, 1, ty_real);
global.MADX9_ShaderResetHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderResetHLSL9", dll_cdecl, ty_real, 0);
global.MADX9_ShaderDestroyHLSL9 = external_define(global.DLL_MADX9, "MADX9_ShaderDestroyHLSL9", dll_cdecl, ty_real, 1, ty_real);

//Initilize
external_call(global.MADX9_Init, window_device());
