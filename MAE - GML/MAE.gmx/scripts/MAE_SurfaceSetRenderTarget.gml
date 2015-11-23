///MAE_SurfaceSetRenderTarget(ind,[level])

/**
 * Description:
 *   Sets a render target
 *
 * Arguments:
 *   [1] - Render target to be set
 *   [2] - Level of the render target
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

var level = 0;

if (argument_count > 1)
    level = argument[1];

return external_call(global.MADX9_SurfaceSetRenderTarget, argument0, level);
