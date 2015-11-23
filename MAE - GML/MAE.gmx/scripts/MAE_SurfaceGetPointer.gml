///MAE_SurfaceGetPointer(ind)

/**
 * Description:
 *   Returns a pointer to the surface. Must be freed by MAE_FreePointer
 *
 * Arguments:
 *   [1] - Surface index
 *
 * Returns:
 *   A null pointer on error, otherwise a valid pointer
 */

return external_call(global.MADX9_SurfaceGetPointer, argument0);
