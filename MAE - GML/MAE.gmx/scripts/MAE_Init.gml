///MAE_Init([flags],[DX9_DLL],[Bullet_DLL])
var flags = INIT_ALL;

global.DLL_MADX9 = "MA_DX9.dll";
global.DLL_MABullet = "MA_Bullet.dll";

if (argument_count > 0 && is_real(argument[0]) && argument[0] != 0)
    flags = argument[0];

if (argument_count > 1 && is_string(argument[1]))
    global.DLL_MADX9 = argument[1];

if (argument_count > 2 && is_string(argument[2]))
    global.DLL_MABullet = argument[2];
    
// Private
global.MADX9_Init = external_define(global.DLL_MADX9, "MADX9_Init", dll_cdecl, ty_real, 1, ty_string);
global.MADX9_Free = external_define(global.DLL_MADX9, "MADX9_Free", dll_cdecl, ty_real, 0);

external_call(global.MADX9_Init, window_device());

if (argument[0] & INIT_RENDER)
{
    //Shaders
    global.MADX9_ShaderCreateHLSL9      = external_define(global.DLL_MADX9, "MADX9_ShaderCreateHLSL9", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_ShaderCreateASM        = external_define(global.DLL_MADX9, "MADX9_ShaderCreateASM", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_ShaderSet              = external_define(global.DLL_MADX9, "MADX9_ShaderSet", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_ShaderReset            = external_define(global.DLL_MADX9, "MADX9_ShaderReset", dll_cdecl, ty_real, 0);
    global.MADX9_ShaderDestroy          = external_define(global.DLL_MADX9, "MADX9_ShaderDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_ShaderFindConstant     = external_define(global.DLL_MADX9, "MADX9_ShaderFindConstant", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_string);
    global.MADX9_ShaderGetSampler       = external_define(global.DLL_MADX9, "MADX9_ShaderGetSampler", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantFloat = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantFloat", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantVec2  = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantVec2", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantVec3  = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantVec3", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantVec4  = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantVec4", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantMat3  = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantMat3", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MADX9_ShaderSetConstantMat4  = external_define(global.DLL_MADX9, "MADX9_ShaderSetConstantMat4", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    
    //Materials
    global.MADX9_MaterialCreate           = external_define(global.DLL_MADX9, "MADX9_MaterialCreate", dll_cdecl, ty_real, 0);
    global.MADX9_MaterialDestroy          = external_define(global.DLL_MADX9, "MADX9_MaterialDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_MaterialSetDiffuse       = external_define(global.DLL_MADX9, "MADX9_MaterialSetDiffuse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MaterialSetAmbient       = external_define(global.DLL_MADX9, "MADX9_MaterialSetAmbient", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MaterialSetSpecular      = external_define(global.DLL_MADX9, "MADX9_MaterialSetSpecular", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MaterialSetSpecularPower = external_define(global.DLL_MADX9, "MADX9_MaterialSetSpecularPower", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_MaterialSetEmissive      = external_define(global.DLL_MADX9, "MADX9_MaterialSetEmissive", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MaterialSet              = external_define(global.DLL_MADX9, "MADX9_MaterialSet", dll_cdecl, ty_real, 1, ty_real); 
    
    //Lights
    global.MADX9_LightCreate          = external_define(global.DLL_MADX9, "MADX9_LightCreate", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_LightDestroy         = external_define(global.DLL_MADX9, "MADX9_LightDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_LightSetDiffuse      = external_define(global.DLL_MADX9, "MADX9_LightSetDiffuse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_LightSetPosition     = external_define(global.DLL_MADX9, "MADX9_LightSetPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_LightSetRange        = external_define(global.DLL_MADX9, "MADX9_LightSetRange", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation0 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation0", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation1 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation1", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightSetAttenuation2 = external_define(global.DLL_MADX9, "MADX9_LightSetAttenuation2", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightEnable          = external_define(global.DLL_MADX9, "MADX9_LightEnable", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_LightDisable         = external_define(global.DLL_MADX9, "MADX9_LightDisable", dll_cdecl, ty_real, 1, ty_real);
    
    //MD2
    global.MADX9_MD2Load      = external_define(global.DLL_MADX9, "MADX9_MD2Load", dll_cdecl, ty_real, 2, ty_string, ty_real);
    global.MADX9_MD2Render    = external_define(global.DLL_MADX9, "MADX9_MD2Render", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MD2GetFrames = external_define(global.DLL_MADX9, "MADX9_MD2GetFrames", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_MD2Destroy   = external_define(global.DLL_MADX9, "MADX9_MD2Destroy", dll_cdecl, ty_real, 1, ty_real);
    
    //X
    global.MADX9_XLoad    = external_define(global.DLL_MADX9, "MADX9_XLoad", dll_cdecl, ty_real, 2, ty_string, ty_string);
    global.MADX9_XRender  = external_define(global.DLL_MADX9, "MADX9_XRender", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_XDestroy = external_define(global.DLL_MADX9, "MADX9_XDestroy", dll_cdecl, ty_real, 1, ty_real);
    
    // Error
    global.MADX9_ErrorSetFlags = external_define(global.DLL_MADX9, "MADX9_ErrorSetFlags", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_ErrorEmpty    = external_define(global.DLL_MADX9, "MADX9_ErrorEmpty", dll_cdecl, ty_real, 0);
    global.MADX9_ErrorPop      = external_define(global.DLL_MADX9, "MADX9_ErrorPop", dll_cdecl, ty_string, 0);
    
    // Textures
    global.MADX9_TextureCreateFromFile         = external_define(global.DLL_MADX9, "MADX9_TextureCreateFromFile", dll_cdecl, ty_real, 2, ty_string, ty_real);
    global.MADX9_TextureCreateFromPointer      = external_define(global.DLL_MADX9, "MADX9_TextureCreateFromPointer", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureDestroy                = external_define(global.DLL_MADX9, "MADX9_TextureDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureSet                    = external_define(global.DLL_MADX9, "MADX9_TextureSet", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureCreateFromFileInMemory = external_define(global.DLL_MADX9, "MADX9_TextureCreateFromFileInMemory", dll_cdecl, ty_real, 3, ty_string, ty_real, ty_real);
    global.MADX9_TextureCreate                 = external_define(global.DLL_MADX9, "MADX9_TextureCreate", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_TextureGenerateMipMaps        = external_define(global.DLL_MADX9, "MADX9_TextureGenerateMipMaps", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureGetPointer             = external_define(global.DLL_MADX9, "MADX9_TextureGetPointer", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureGetSurfaceCount        = external_define(global.DLL_MADX9, "MADX9_TextureGetSurfaceCount", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_TextureSetMipMapFilter        = external_define(global.DLL_MADX9, "MADX9_TextureSetMipMapFilter", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_TextureUpdate                 = external_define(global.DLL_MADX9, "MADX9_TextureUpdate", dll_cdecl, ty_real, 2, ty_real, ty_real);
    
    // Misc
    global.MADX9_SetSamplerState = external_define(global.DLL_MADX9, "MADX9_SetSamplerState", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MADX9_SetRenderState  = external_define(global.DLL_MADX9, "MADX9_SetRenderState", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_FreePointer     = external_define(global.DLL_MADX9, "MADX9_FreePointer", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_Clear           = external_define(global.DLL_MADX9, "MADX9_Clear", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_IsNullPointer   = external_define(global.DLL_MADX9, "MADX9_IsNullPointer", dll_cdecl, ty_real, 1, ty_real);
    
    // Internal
    global.MADX9_MatStackFloat8 = external_define(global.DLL_MADX9, "MADX9_MatStackFloat8", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MatStackFloat9 = external_define(global.DLL_MADX9, "MADX9_MatStackFloat9", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_MatStackClear  = external_define(global.DLL_MADX9, "MADX9_MatStackClear", dll_cdecl, ty_real, 0);
    
    // Hook
    global.MADX9_HookEnable             = external_define(global.DLL_MADX9, "MADX9_HookEnable", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_HookDisable            = external_define(global.DLL_MADX9, "MADX9_HookDisable", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_HookStackPopPointer    = external_define(global.DLL_MADX9, "MADX9_HookStackPopPointer", dll_cdecl, ty_real, 0);
    global.MADX9_HookStackClear         = external_define(global.DLL_MADX9, "MADX9_HookStackClear", dll_cdecl, ty_real, 0);
    global.MADX9_HookStackEmpty         = external_define(global.DLL_MADX9, "MADX9_HookStackEmpty", dll_cdecl, ty_real, 0);
    global.MADX9_HookSetPropertyNull    = external_define(global.DLL_MADX9, "MADX9_HookSetPropertyNull", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_HookSetPropertyInt     = external_define(global.DLL_MADX9, "MADX9_HookSetPropertyInt", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_HookSetPropertyPointer = external_define(global.DLL_MADX9, "MADX9_HookSetPropertyPointer", dll_cdecl, ty_real, 2, ty_real, ty_real);
    
    // Surfaces
    global.MADX9_SurfaceCreateDepthStencil = external_define(global.DLL_MADX9, "MADX9_SurfaceCreateDepthStencil", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_SurfaceCreateFromPointer  = external_define(global.DLL_MADX9, "MADX9_SurfaceCreateFromPointer", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_SurfaceCreateFromTexture  = external_define(global.DLL_MADX9, "MADX9_SurfaceCreateFromTexture", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_SurfaceCreateRenderTarget = external_define(global.DLL_MADX9, "MADX9_SurfaceCreateRenderTarget", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MADX9_SurfaceDestroy            = external_define(global.DLL_MADX9, "MADX9_SurfaceDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_SurfaceSetRenderTarget    = external_define(global.DLL_MADX9, "MADX9_SurfaceSetRenderTarget", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_SurfaceResetRenderTarget  = external_define(global.DLL_MADX9, "MADX9_SurfaceResetRenderTarget", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_SurfaceSetDepthBuffer     = external_define(global.DLL_MADX9, "MADX9_SurfaceSetDepthBuffer", dll_cdecl, ty_real, 1, ty_real);
    global.MADX9_SurfaceResetDepthBuffer   = external_define(global.DLL_MADX9, "MADX9_SurfaceResetDepthBuffer", dll_cdecl, ty_real, 0);
    global.MADX9_SurfaceUpdate             = external_define(global.DLL_MADX9, "MADX9_SurfaceUpdate", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MADX9_SurfaceGetPointer         = external_define(global.DLL_MADX9, "MADX9_SurfaceGetPointer", dll_cdecl, ty_real, 1, ty_real);
}

if (argument[0] & INIT_FLUSH)
{
    MAE_HookEnable(HOOK_ACTIONFETCHVERTDECL);
    
    vertex_format_begin();
    vertex_format_add_colour();
    var f = vertex_format_end();
    
    MAE_HookDisable(HOOK_ACTIONFETCHVERTDECL);
    
    var p = MAE_HookStackPopPointer();
    
    MAE_HookSetPropertyPointer(HOOK_PROPERTYDISABLEVERTDECL, p);
    MAE_HookEnable(HOOK_ACTIONIGNOREVERTDECL);
    
    MAE_FreePointer(p);
    
    global.MAE_FlushBuffer = vertex_create_buffer_ext(4);
    vertex_begin(global.MAE_FlushBuffer, f);
    vertex_colour(global.MAE_FlushBuffer, 0, 0);
    vertex_end(global.MAE_FlushBuffer);
}

if (argument[0] & INIT_PHYSICS)
{
    global.MAB_Free = external_define(global.DLL_MABullet, "MAB_Free", dll_cdecl, ty_real, 0);
    
    //World
    global.MAB_WorldCreate             = external_define(global.DLL_MABullet, "MAB_WorldCreate", dll_cdecl, ty_real, 0);
    global.MAB_WorldDestroy            = external_define(global.DLL_MABullet, "MAB_WorldDestroy", dll_cdecl, ty_real, 0);
    global.MAB_WorldStep               = external_define(global.DLL_MABullet, "MAB_WorldStep", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_WorldSetGravity         = external_define(global.DLL_MABullet, "MAB_WorldSetGravity", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_WorldGetGravity         = external_define(global.DLL_MABullet, "MAB_WorldGetGravity", dll_cdecl, ty_real, 0);
    global.MAB_WorldGetBodyCount       = external_define(global.DLL_MABullet, "MAB_WorldGetBodyCount", dll_cdecl, ty_real, 0);
    global.MAB_WorldGetConstraintCount = external_define(global.DLL_MABullet, "MAB_WorldGetConstraintCount", dll_cdecl, ty_real, 0);
    global.MAB_WorldExists             = external_define(global.DLL_MABullet, "MAB_WorldExists", dll_cdecl, ty_real, 0);
    global.MAB_WorldDebugDraw          = external_define(global.DLL_MABullet, "MAB_WorldDebugDraw", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_WorldRaycast            = external_define(global.DLL_MABullet, "MAB_WorldRaycast", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_WorldSweep              = external_define(global.DLL_MABullet, "MAB_WorldSweep", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_WorldOverlap            = external_define(global.DLL_MABullet, "MAB_WorldOverlap", dll_cdecl, ty_real, 10, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    
    //Misc
    global.MAB_Vec           = external_define(global.DLL_MABullet, "MAB_Vec", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_Quat          = external_define(global.DLL_MABullet, "MAB_Quat", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_HitResult     = external_define(global.DLL_MABullet, "MAB_HitResult", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_OverlapResult = external_define(global.DLL_MABullet, "MAB_OverlapResult", dll_cdecl, ty_real, 1, ty_real);
    
    //Shape
    global.MAB_ShapeCreateBox            = external_define(global.DLL_MABullet, "MAB_ShapeCreateBox", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreateSphere         = external_define(global.DLL_MABullet, "MAB_ShapeCreateSphere", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_ShapeCreateCapsule        = external_define(global.DLL_MABullet, "MAB_ShapeCreateCapsule", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreateCylinder       = external_define(global.DLL_MABullet, "MAB_ShapeCreateCylinder", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreateCone           = external_define(global.DLL_MABullet, "MAB_ShapeCreateCone", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreatePlane          = external_define(global.DLL_MABullet, "MAB_ShapeCreatePlane", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreateCompound       = external_define(global.DLL_MABullet, "MAB_ShapeCreateCompound", dll_cdecl, ty_real, 0);
    global.MAB_ShapeAddChild             = external_define(global.DLL_MABullet, "MAB_ShapeAddChild", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ShapeRemoveChild          = external_define(global.DLL_MABullet, "MAB_ShapeRemoveChild", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_ShapeUpdateChildTransform = external_define(global.DLL_MABullet, "MAB_ShapeUpdateChildTransform", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ShapeCreateTriMesh        = external_define(global.DLL_MABullet, "MAB_ShapeCreateTriMesh", dll_cdecl, ty_real, 4, ty_real, ty_string, ty_real, ty_real);
    global.MAB_ShapeCreateConvexHull     = external_define(global.DLL_MABullet, "MAB_ShapeCreateConvexHull", dll_cdecl, ty_real, 2, ty_string, ty_real);
    global.MAB_ShapeDestroy              = external_define(global.DLL_MABullet, "MAB_ShapeDestroy", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_ShapeDestroyAll           = external_define(global.DLL_MABullet, "MAB_ShapeDestroyAll", dll_cdecl, ty_real, 0);
    global.MAB_ShapeSetMargin            = external_define(global.DLL_MABullet, "MAB_ShapeSetMargin", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_ShapeSetScaling           = external_define(global.DLL_MABullet, "MAB_ShapeSetScaling", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    
    //Body
    global.MAB_BodyCreate                 = external_define(global.DLL_MABullet, "MAB_BodyCreate", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyDestroy                = external_define(global.DLL_MABullet, "MAB_BodyDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetPosition            = external_define(global.DLL_MABullet, "MAB_BodyGetPosition", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetRotationQuat        = external_define(global.DLL_MABullet, "MAB_BodyGetRotationQuat", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetRotationEuler       = external_define(global.DLL_MABullet, "MAB_BodyGetRotationEuler", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetLinearVelocity      = external_define(global.DLL_MABullet, "MAB_BodyGetLinearVelocity", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetAngularVelocity     = external_define(global.DLL_MABullet, "MAB_BodyGetAngularVelocity", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetAnisotropicFriction = external_define(global.DLL_MABullet, "MAB_BodyGetAngularVelocity", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetGravity             = external_define(global.DLL_MABullet, "MAB_BodyGetGravity", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetAngularDamping      = external_define(global.DLL_MABullet, "MAB_BodyGetAngularDamping", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetLinearDamping       = external_define(global.DLL_MABullet, "MAB_BodyGetLinearDamping", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetFriction            = external_define(global.DLL_MABullet, "MAB_BodyGetFriction", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetRestitution         = external_define(global.DLL_MABullet, "MAB_BodyGetRestitution", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetRollingFriction     = external_define(global.DLL_MABullet, "MAB_BodyGetRollingFriction", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetUserIndex           = external_define(global.DLL_MABullet, "MAB_BodyGetUserIndex", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetDeactivationTime    = external_define(global.DLL_MABullet, "MAB_BodyGetDeactivationTime", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetIgnore              = external_define(global.DLL_MABullet, "MAB_BodyGetIgnore", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodyIsStatic               = external_define(global.DLL_MABullet, "MAB_BodyIsStatic", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyIsKinematic            = external_define(global.DLL_MABullet, "MAB_BodyIsKinematic", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetShape               = external_define(global.DLL_MABullet, "MAB_BodyGetShape", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyIsActive               = external_define(global.DLL_MABullet, "MAB_BodyIsActive", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetGroup               = external_define(global.DLL_MABullet, "MAB_BodyGetGroup", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyGetMask                = external_define(global.DLL_MABullet, "MAB_BodyGetMask", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodySetIgnore              = external_define(global.DLL_MABullet, "MAB_BodySetIgnore", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_BodySetPosition            = external_define(global.DLL_MABullet, "MAB_BodySetPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetRotationQuat        = external_define(global.DLL_MABullet, "MAB_BodySetRotationQuat", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetRotationEuler       = external_define(global.DLL_MABullet, "MAB_BodySetRotationEuler", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetLinearVelocity      = external_define(global.DLL_MABullet, "MAB_BodySetLinearVelocity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetAngularVelocity     = external_define(global.DLL_MABullet, "MAB_BodySetAngularVelocity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetLinearFactor        = external_define(global.DLL_MABullet, "MAB_BodySetLinearFactor", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetAngularFactor       = external_define(global.DLL_MABullet, "MAB_BodySetAngularFactor", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetDamping             = external_define(global.DLL_MABullet, "MAB_BodySetDamping", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_BodySetFriction            = external_define(global.DLL_MABullet, "MAB_BodySetFriction", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodySetAnisotropicFriction = external_define(global.DLL_MABullet, "MAB_BodySetAnisotropicFriction", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetRestitution         = external_define(global.DLL_MABullet, "MAB_BodySetRestitution", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodySetRollingFriction     = external_define(global.DLL_MABullet, "MAB_BodySetRollingFriction", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodySetUserIndex           = external_define(global.DLL_MABullet, "MAB_BodySetUserIndex", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodySetGravity             = external_define(global.DLL_MABullet, "MAB_BodySetGravity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodySetDeactivationTime    = external_define(global.DLL_MABullet, "MAB_BodySetDeactivationTime", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodyDisableDeactivation    = external_define(global.DLL_MABullet, "MAB_BodyDisableDeactivation", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyActivate               = external_define(global.DLL_MABullet, "MAB_BodyActivate", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodyDeactivate             = external_define(global.DLL_MABullet, "MAB_BodyDeactivate", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_BodySetShape               = external_define(global.DLL_MABullet, "MAB_BodySetShape", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_BodySetGroupMask           = external_define(global.DLL_MABullet, "MAB_BodySetGroupMask", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyCentralImpulse    = external_define(global.DLL_MABullet, "MAB_BodyApplyCentralImpulse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyCentralForce      = external_define(global.DLL_MABullet, "MAB_BodyApplyCentralForce", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyImpulse           = external_define(global.DLL_MABullet, "MAB_BodyApplyImpulse", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyForce             = external_define(global.DLL_MABullet, "MAB_BodyApplyForce", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyTorque            = external_define(global.DLL_MABullet, "MAB_BodyApplyTorque", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_BodyApplyTorqueImpulse     = external_define(global.DLL_MABullet, "MAB_BodyApplyTorqueImpulse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
    
    //Constraints
    global.MAB_ConstraintCreateP2P         = external_define(global.DLL_MABullet, "MAB_ConstraintCreateP2P", dll_cdecl, ty_real, 11, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreateFixed       = external_define(global.DLL_MABullet, "MAB_ConstraintCreateFixed", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_ConstraintCreateSlider      = external_define(global.DLL_MABullet, "MAB_ConstraintCreateSlider", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreateGear        = external_define(global.DLL_MABullet, "MAB_ConstraintCreateGear", dll_cdecl, ty_real, 10, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreateHinge       = external_define(global.DLL_MABullet, "MAB_ConstraintCreateHinge", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreate6DOF        = external_define(global.DLL_MABullet, "MAB_ConstraintCreate6DOF", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreateSpring6DOF  = external_define(global.DLL_MABullet, "MAB_ConstraintCreateSpring6DOF", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintCreateConeTwist   = external_define(global.DLL_MABullet, "MAB_ConstraintCreateConeTwist", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
    global.MAB_ConstraintParamTransform    = external_define(global.DLL_MABullet, "MAB_ConstraintParamTransform", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    global.MAB_ConstraintSetEnabled        = external_define(global.DLL_MABullet, "MAB_ConstraintSetEnabled", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global.MAB_ConstraintDestroy           = external_define(global.DLL_MABullet, "MAB_ConstraintDestroy", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_ConstraintGetAppliedImpulse = external_define(global.DLL_MABullet, "MAB_ConstraintGetAppliedImpulse", dll_cdecl, ty_real, 1, ty_real);
    global.MAB_ConstraintSetParam          = external_define(global.DLL_MABullet, "MAB_ConstraintSetParam", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
    
    //Constraint Params
    enum PARAM {
        IMPULSE_CLAMP,
        DAMPING,
        TAU,
        PIVOTA,
        PIVOTB,
        BREAK_THRESHOLD,
    };
}
