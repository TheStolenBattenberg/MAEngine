///MAE_TextureCreateFromFile(index,file,[mipmaps])

/**
 * Description:
 *   Creates a texture from a file
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - File to be loaded
 *   [3] - Mip Map Type (MIPMAPS_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var m = MIPMAPS_NONE;

if (argument_count > 2)
    m = argument[2];

return external_call(global.MADX9_TextureCreateFromFile, argument[0], argument[1], m);
