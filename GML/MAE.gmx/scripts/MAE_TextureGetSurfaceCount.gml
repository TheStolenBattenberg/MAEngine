///MAE_TextureGetSurfaceCount(ind)

/**
 * Description:
 *   Gets number of surfaces/levels inside the texture
 *
 * Arguments:
 *   [1] - Texture index
 *
 * Returns:
 *   -1 on error, otherwise number of surfaces/levels
 */

return external_call(global.MADX9_TextureGetSurfaceCount, argument0);
