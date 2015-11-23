///MAE_SurfaceCreateDepthStencil(width,height,format,ms,msquality,discard)

/**
 * Description:
 *   Creates a depht buffer with an optional stencil buffer.
 *
 * Arguments:
 *   [1] - Witdth of the buffer
 *   [2] - Height of the buffer
 *   [3] - Format of the buffer (FMT_D*)
 *   [4] - Multisample type (MULTISAMPLE_*)
 *   [5] - Multisample quality
 *   [6] - Discard buffer after calling present.
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateDepthStencil, argument0, argument1, argument2, argument3, argument4, argument5);
