///MAE_SurfaceCreateFromTexture(tex,level)

/**
 * Description:
 *   Creates surface from a texture.
 *
 * Arguments:
 *   [1] - Texture index
 *   [2] - Level on the texture
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateFromTexture, argument0, argument1);
