///MAE_SurfaceCreateRenderTarget(index,width,height,format,ms,msquality,lockable)

/**
 * Description:
 *   Creates a render target.
 *
 * Arguments:
 *   [1] - Index of the surface
 *   [2] - Witdth of the buffer
 *   [3] - Height of the buffer
 *   [4] - Format of the buffer (FMT_*)
 *   [5] - Multisample type (MULTISAMPLE_*)
 *   [6] - Multisample quality
 *   [7] - Make render target lockable
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateRenderTarget, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
