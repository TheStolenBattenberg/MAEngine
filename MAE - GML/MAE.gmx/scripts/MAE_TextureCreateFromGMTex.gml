///MAE_TextureCreateFromGMTex(tex)

/**
 * Description:
 *   Creates a texture from a game maker texture pointer.
 *   Requires INIT_HOOKS and INIT_FLUSH
 *
 * Arguments:
 *   [1] - Game Maker texture
 *
 * Returns:
 *   Texture index or -1 on failure.
 */

var t;

draw_primitive_begin_texture(pr_pointlist, argument0);
draw_vertex(0, 0);
draw_primitive_end();

MAE_HookEnable(HOOK_FETCHTEXSET);
MAE_Flush();
MAE_HookDisable(HOOK_FETCHTEXSET);

if (MAE_HookStackEmpty())
    return -1;

var p = MAE_HookStackPopPointer();

var t = MAE_TextureCreateFromPointer(p);

MAE_FreePointer(p);

return t;
