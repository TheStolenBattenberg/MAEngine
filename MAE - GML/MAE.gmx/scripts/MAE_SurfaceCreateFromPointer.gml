///MAE_SurfaceCreateFromPointer(index,ptr)

/**
 * Description:
 *   Creates a surface from a pointer.
 *
 * Arguments:
 *   [1] - Index to surface
 *   [2] - Pointer to surface
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateFromPointer, argument0, argument1);
