///MAE_TextureCreateFromFileInMemory(index,buffer,[mipmaps])

/**
 * Description:
 *   Creates a texture from a file in memory
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - Buffer which contains the file
 *   [3] - Mip Map Type (MIPMAPS_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var m = MIPMAPS_NONE;

if (argument_count > 2)
    m = argument[2];

return external_call(global.MADX9_TextureCreateFromFileInMemory, argument[0], buffer_get_address(argument[1]), buffer_get_size(argument[1]), m);
