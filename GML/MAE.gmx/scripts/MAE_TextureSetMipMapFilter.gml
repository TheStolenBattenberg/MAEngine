///MAE_TextureSetMipMapFilter(ind,filter)

/**
 * Description:
 *   Sets the filter to be used when generating MipMaps for a texture
 *   created with USAGE_AUTOGENMIPMAP
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - Filter (TEXF_*)
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_TextureSetMipMapFilter, argument0, argument1);
