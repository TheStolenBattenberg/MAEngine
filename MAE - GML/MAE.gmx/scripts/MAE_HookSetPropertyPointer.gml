///MAE_HookSetPropertyPointer(prop,value)

/**
 * Description:
 *   Sets a property to a pointer value.
 *
 * Arguments:
 *   [1] - Property (HOOK_PROPERTY*)
 *   [2] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_HookSetPropertyPointer, argument0, argument1);
