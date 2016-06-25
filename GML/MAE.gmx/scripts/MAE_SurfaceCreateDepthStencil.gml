///MAE_SurfaceCreateDepthStencil(index,width,height,format,ms,msquality,discard)

/**
 * Description:
 *   Creates a depht buffer with an optional stencil buffer.
 *
 * Arguments:
 *   [1] - Index of the surface
 *   [2] - Witdth of the buffer
 *   [3] - Height of the buffer
 *   [4] - Format of the buffer (FMT_D*)
 *   [5] - Multisample type (MULTISAMPLE_*)
 *   [6] - Multisample quality
 *   [7] - Discard buffer after calling present.
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateDepthStencil, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
