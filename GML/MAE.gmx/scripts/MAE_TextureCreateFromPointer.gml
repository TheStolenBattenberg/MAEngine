///MAE_TextureCreateFromPointer(index,ptr)

/**
 * Description:
 *   Creates a texture from a pointer.
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - Pointer to a texture
 *
 * Returns:
 *   Texture index or -1 on failure.
 */

return external_call(global.MADX9_TextureCreateFromPointer, argument0, argument1);
