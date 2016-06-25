///MAE_FreePointer(ptr)

/**
 * Description:
 *   Frees pointer to any Direct3D resource.
 *
 * Arguments:
 *   [1] - Pointer of the resource
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_FreePointer, argument0);
