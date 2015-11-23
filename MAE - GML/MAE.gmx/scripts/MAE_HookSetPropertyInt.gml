///MAE_HookSetPropertyInt(prop,value)

/**
 * Description:
 *   Sets a property to an integer value.
 *
 * Arguments:
 *   [1] - Property (HOOK_PROPERTY*)
 *   [2] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_HookSetPropertyInt, argument0, argument1);
