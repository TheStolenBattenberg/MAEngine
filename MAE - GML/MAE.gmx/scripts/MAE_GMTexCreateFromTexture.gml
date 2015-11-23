///MAE_GMTexCreateFromTexture(ind)

/**
 * Description:
 *   Creates a game maker texture from a texture
 *
 * Arguments:
 *   [1] - Texture index
 *
 * Returns:
 *   game maker texture
 */

MAE_HookEnable(HOOK_ACTIONFETCHTEXCREATE);

var b = background_create_colour(1, 1, c_white);

MAE_HookDisable(HOOK_ACTIONFETCHTEXCREATE);

MAE_HookStackPopPointer();
var tb = MAE_HookStackPopPointer();
MAE_HookStackClear();

var t = MAE_TextureGetPointer(argument0);

MAE_HookSetPropertyPointer(HOOK_PROPERTYREDIRECTTEXFROM, tb);
MAE_HookSetPropertyPointer(HOOK_PROPERTYREDIRECTTEXTO, t);
MAE_HookEnable(HOOK_ACTIONREDIRECTTEXTURE);

MAE_FreePointer(t);

return background_get_texture(b);
