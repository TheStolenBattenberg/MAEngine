///MAE_TextureCreateFromFile(file,[mipmaps])

/**
 * Description:
 *   Creates a texture from a file
 *
 * Arguments:
 *   [1] - File to be loaded
 *   [2] - Mip Map Type (MIPMAPS_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var m = MIPMAPS_NONE;

if (argument_count > 1)
    m = argument[1];

return external_call(global.MADX9_TextureCreateFromFile, argument[0], m);
