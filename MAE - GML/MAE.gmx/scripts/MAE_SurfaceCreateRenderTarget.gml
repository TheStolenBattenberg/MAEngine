///MAE_SurfaceCreateRenderTarget(width,height,format,ms,msquality,lockable)

/**
 * Description:
 *   Creates a render target.
 *
 * Arguments:
 *   [1] - Witdth of the buffer
 *   [2] - Height of the buffer
 *   [3] - Format of the buffer (FMT_*)
 *   [4] - Multisample type (MULTISAMPLE_*)
 *   [5] - Multisample quality
 *   [6] - Make render target lockable
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateRenderTarget, argument0, argument1, argument2, argument3, argument4, argument5);
