///MAE_SurfaceResetRenderTarget([level])

/**
 * Description:
 *   Resets the render target
 *
 * Arguments:
 *   [1] - Level of the render target
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

var level = 0;

if (argument_count > 0)
    level = argument[0];

return external_call(global.MADX9_SurfaceResetRenderTarget, level);
