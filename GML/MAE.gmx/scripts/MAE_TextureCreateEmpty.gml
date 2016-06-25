///MAE_TextureCreateEmpty(index,width,height,levels,usage,format,pool)

/**
 * Description:
 *   Creates a empty texture
 *
 * Arguments:
 *   [1] - Index of the texture
 *   [2] - Width
 *   [3] - Height
 *   [4] - Levels of the texture
 *   [5] - Usage (USAGE_*)
 *   [6] - Format (FMT_*)
 *   [7] - Pool (POOL_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

return external_call(global.MADX9_TextureCreateEmpty, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
