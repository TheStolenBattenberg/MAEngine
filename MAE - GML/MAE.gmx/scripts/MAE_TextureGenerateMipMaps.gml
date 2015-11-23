///MAE_TextureGenerateMipMaps(ind)

/**
 * Description:
 *   Generates MipMaps for a texture created with USAGE_AUTOGENMIPMAP
 *
 * Arguments:
 *   [1] - Index of the texture
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_TextureGenerateMipMaps, argument0);
