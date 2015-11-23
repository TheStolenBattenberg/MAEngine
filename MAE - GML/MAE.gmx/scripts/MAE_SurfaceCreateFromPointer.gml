///MAE_SurfaceCreateFromPointer(ptr)

/**
 * Description:
 *   Creates a surface from a pointer.
 *
 * Arguments:
 *   [1] - Pointer to surface
 *
 * Returns:
 *   -1 on Error, surface index on success.
 */

return external_call(global.MADX9_SurfaceCreateFromPointer, argument0);
