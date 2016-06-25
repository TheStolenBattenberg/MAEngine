///MAE_SurfaceDestroy(ind)

/**
 * Description:
 *   Destroys a surface
 *
 * Arguments:
 *   [1] - Index of the surface
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_SurfaceDestroy, argument0);
