///MAE_TextureCreateFromFileInMemory(buffer,[mipmaps])

/**
 * Description:
 *   Creates a texture from a file in memory
 *
 * Arguments:
 *   [1] - Buffer which contains the file
 *   [2] - Mip Map Type (MIPMAPS_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

var m = MIPMAPS_NONE;

if (argument_count > 1)
    m = argument[1];

return external_call(global.MADX9_TextureCreateFromFileInMemory, buffer_get_address(argument[0]), buffer_get_size(argument[0]), m);
