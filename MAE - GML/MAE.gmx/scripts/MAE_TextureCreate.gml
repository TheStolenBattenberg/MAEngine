///MAE_TextureCreate(width,height,levels,usage,format,pool)

/**
 * Description:
 *   Creates a texture
 *
 * Arguments:
 *   [1] - Width
 *   [2] - Height
 *   [3] - Levels of the texture
 *   [4] - Usage (USAGE_*)
 *   [5] - Format (FMT_*)
 *   [6] - Pool (POOL_*)
 *
 * Returns:
 *   -1 on Error, texture index on success.
 */

return external_call(global.MADX9_TextureCreate, argument0, argument1, argument2, argument3, argument4, argument5);
