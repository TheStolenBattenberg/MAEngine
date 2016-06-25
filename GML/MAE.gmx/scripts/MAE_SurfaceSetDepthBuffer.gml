///MAE_SurfaceSetDepthBuffer(ind)

/**
 * Description:
 *   Sets the depth buffer
 *
 * Arguments:
 *   [1] - Depth buffer to be set.
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_SurfaceSetDepthBuffer, argument0);
