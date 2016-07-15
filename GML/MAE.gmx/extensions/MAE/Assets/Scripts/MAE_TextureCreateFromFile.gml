///MAE_TextureCreateFromFile(file,mipmaps = MIPMAPS_NONE);

/**
 * Description:
 *   Creates a texture from a file
 *
 * Arguments:
 *   [1] - File to be loaded
 *   [2] - Mip Map Type (MIPMAPS_ )
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var _mipmaps = MIPMAPS_NONE;

if (argument_count > 1)
    _mipmaps = argument[1];

return external_call(global._MADX9_TextureCreateFromFile, argument[0], _mipmaps);
