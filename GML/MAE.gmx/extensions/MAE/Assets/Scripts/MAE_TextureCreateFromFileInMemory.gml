///MAE_TextureCreateFromFileInMemory(index,buffer,mipmaps = MIPMAPS_NONE);

/**
 * Description:
 *   Creates a texture from a file in memory
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - Buffer which contains the file
 *   [3] - Mip Map Type (MIPMAPS_ )
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var _mipmaps = MIPMAPS_NONE;

if (argument_count > 2)
    _mipmaps = argument[2];

return external_call(global._MADX9_TextureCreateFromFileInMemory, argument[0], buffer_get_address(argument[1]), buffer_get_size(argument[1]), _mipmaps);
